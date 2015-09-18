//----------------------------------------------------------------------
//
// Filename    : GameServerGroupInfoManager.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#include "GameServerGroupInfoManager.h"

#include "database/DatabaseManager.h"
#include "database/Connection.h"
#include "database/Statement.h"
#include "database/Result.h"
#include "database/DB.h"

GameServerGroupInfoManager::GameServerGroupInfoManager() throw() {
    m_MaxWorldID = 0;
}

GameServerGroupInfoManager::~GameServerGroupInfoManager() throw() {
    clear();
}

void GameServerGroupInfoManager::clear() throw(Error) {
/*
    __BEGIN_TRY

    // hashmap ���� �� pair �� second, �� GameServerGroupInfo ��ü���� �����ϰ�
    // pair ��ü�� �״�� �д�. (GameServerGroupInfo�� ���� �����Ǿ� �ִٴ� �Ϳ�
    // �����϶�. �� �ʻ������ �ؾ� �Ѵ�. �ϱ�, GSIM�� destruct �ȴٴ� ����
    // �α��� ������ �˴ٿ�ȴٴ� ���� �ǹ��ϴϱ�.. - -; )
    for(int i = 1 ; i < m_MaxWorldID; i++ ) {
        for (HashMapGameServerGroupInfo::iterator itr = m_GameServerGroupInfos[i].begin() ; 
              itr != m_GameServerGroupInfos[i].end() ; 
              itr ++ ) {
            SAFE_DELETE(itr->second);
        }

        // ���� �ؽ��ʾȿ� �ִ� ��� pair ���� �����Ѵ�.
        m_GameServerGroupInfos[i].clear();

    }

    SAFE_DELETE_ARRAY(m_GameServerGroupInfos);

    __END_CATCH
*/
}


void GameServerGroupInfoManager::init() throw(Error) {
    __BEGIN_TRY

    // just load data from GameServerGroupInfo table
    load();

    // just print to cout
    cout << toString() << endl;

    __END_CATCH
}


void GameServerGroupInfoManager::load() throw(Error) {
    __BEGIN_TRY

    clear();

    Statement * pStmt = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        Result* pResult = pStmt->executeQuery("SELECT MAX(WorldID) FROM GameServerGroupInfo");

        if (pResult->getRowCount() == 0)
            throw Error("[GameServerGroupInfoManager] TABLE does not exist!");

        pResult->next();
        m_MaxWorldID = pResult->getInt(1) + 2;

        SAFE_DELETE(pStmt);
    } END_DB(pStmt)

    m_GameServerGroupInfos = new HashMapGameServerGroupInfo[m_MaxWorldID];

    try {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        Result * pResult = pStmt->executeQuery("SELECT WorldID, GroupID, GroupName, Stat FROM GameServerGroupInfo");

        while (pResult->next()) {
            GameServerGroupInfo * pGameServerGroupInfo = new GameServerGroupInfo();
            WorldID_t WorldID = pResult->getInt(1);
            pGameServerGroupInfo->setWorldID(WorldID);
            pGameServerGroupInfo->setGroupID(pResult->getInt(2));
            pGameServerGroupInfo->setGroupName(pResult->getString(3));
            pGameServerGroupInfo->setStat(pResult->getInt(4));
            addGameServerGroupInfo(pGameServerGroupInfo, WorldID);
        }
        SAFE_DELETE(pStmt);
    }
    catch (SQLQueryException & sqe) {
        // �ʻ� ����!
        SAFE_DELETE(pStmt);

        throw Error(sqe.toString());
    }
    catch (Throwable & t) {
        SAFE_DELETE(pStmt);
        cout << t.toString() << endl;
    }

    __END_CATCH
}

void GameServerGroupInfoManager::addGameServerGroupInfo(GameServerGroupInfo * pGameServerGroupInfo, WorldID_t WorldID) throw(DuplicatedException) {
    __BEGIN_TRY

    int GroupID = pGameServerGroupInfo->getGroupID();
    HashMapGameServerGroupInfo::iterator itr = m_GameServerGroupInfos[WorldID].find(GroupID);
    
    if (itr != m_GameServerGroupInfos[WorldID].end())
        throw DuplicatedException("[GameServerGroupInfoManager] Duplicated Gameserver Nickname.");

    cout << "addGameServerGroupInfo: " << (int)WorldID << ", " << GroupID << ": " << pGameServerGroupInfo->getGroupName().c_str() << endl;

    m_GameServerGroupInfos[WorldID][GroupID] = pGameServerGroupInfo;

    __END_CATCH
}

void GameServerGroupInfoManager::deleteGameServerGroupInfo(const ServerGroupID_t GroupID, WorldID_t WorldID) throw(NoSuchElementException) {
    __BEGIN_TRY
        
    HashMapGameServerGroupInfo::iterator itr = m_GameServerGroupInfos[WorldID].find(GroupID);
    
    if (itr != m_GameServerGroupInfos[WorldID].end()) {
        delete itr->second;

        m_GameServerGroupInfos[WorldID].erase(itr);
    }
    else
        throw NoSuchElementException("[GameServerGroupInfoManager] GameServer Group not found to delete.");

    __END_CATCH
}
    
GameServerGroupInfo * GameServerGroupInfoManager::getGameServerGroupInfo(const ServerGroupID_t GroupID, WorldID_t WorldID) const throw(NoSuchElementException) {
    __BEGIN_TRY

    if(WorldID >= m_MaxWorldID)
        throw NoSuchElementException("[GameServerGroupInfoManager] WorldID > MaxWorldID.");

    GameServerGroupInfo * pGameServerGroupInfo = NULL;

    HashMapGameServerGroupInfo::const_iterator itr = m_GameServerGroupInfos[WorldID].find(GroupID);

    if (itr != m_GameServerGroupInfos[WorldID].end())
        pGameServerGroupInfo = itr->second;
    else
        throw NoSuchElementException("[GameServerGroupInfoManager] GameServer Group not found.");

    return pGameServerGroupInfo;

    __END_CATCH
}

string GameServerGroupInfoManager::toString() const throw() {
    __BEGIN_TRY

    StringStream msg;

    msg << "GameServerGroupInfoManager(\n";

    for (int i = 1; i < m_MaxWorldID; i++) {
        if (m_GameServerGroupInfos[i].empty())
            msg << "EMPTY";
        else {
            //--------------------------------------------------
            // *OPTIMIZATION*
            //
            // for_each()�� ����� ��
            //--------------------------------------------------
            for (HashMapGameServerGroupInfo::const_iterator itr = m_GameServerGroupInfos[i].begin();
                 itr != m_GameServerGroupInfos[i].end();
                 itr ++)
                msg << itr->second->toString() << '\n';
        }
    }

    msg << ")";

    return msg.toString();

    __END_CATCH
}

GameServerGroupInfoManager * g_pGameServerGroupInfoManager = NULL;