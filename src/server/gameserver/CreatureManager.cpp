//////////////////////////////////////////////////////////////////////////////
// Filename    : CreatureManager.h 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CreatureManager.h"
#include <algorithm>		// find_if ()
#include "Assert.h"
#include "GamePlayer.h"
#include "ZoneGroupManager.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "ZonePlayerManager.h"
#include "IncomingPlayerManager.h"
#include "Player.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Tile.h"
#include "Zone.h"
#include "LogClient.h"
#include "LevelWarZoneInfoManager.h"
#include "SweeperBonusManager.h"

#include "GCCreatureDied.h"

class isSameNAME 
{
public:
	isSameNAME (const string& Name) : m_Name(Name) {}

	bool operator () (pair<const long unsigned int , Creature *> itr) 
	{
		return (itr.second)->getName() == m_Name;
	}

private:
	string m_Name;

};

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
CreatureManager::CreatureManager () 
	
{
	__BEGIN_TRY

	m_Mutex.setName("CreatureManager");

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
CreatureManager::~CreatureManager () 
	
{
	__BEGIN_TRY

	unordered_map<ObjectID_t, Creature*>::iterator itr = m_Creatures.begin();

	for (; itr != m_Creatures.end(); itr++)	
	{
		Creature* pCreature = itr->second;
		SAFE_DELETE(pCreature);
	}

	m_Creatures.clear();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 农府贸 概聪历俊 货 农府贸 按眉甫 殿废茄促.
//////////////////////////////////////////////////////////////////////////////
void CreatureManager::addCreature (Creature* pCreature) 
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	unordered_map< ObjectID_t , Creature* >::iterator itr = m_Creatures.find(pCreature->getObjectID());

	if (itr != m_Creatures.end())	
		throw DuplicatedException();

	m_Creatures[ pCreature->getObjectID() ] = pCreature;

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
// 农府贸 概聪历俊 甸绢乐绰 漂沥 农府贸 按眉甫 昏力茄促.
//////////////////////////////////////////////////////////////////////////////
void CreatureManager::deleteCreature (ObjectID_t objectID) 
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	//try 
	{
		unordered_map< ObjectID_t , Creature* >::iterator itr = m_Creatures.find(objectID);

		if (itr == m_Creatures.end())
		{
			//throw NoSuchElementException();
			// 措面(-_-;) 混旗夯 搬苞 寇何俊辑 NoSuchElementException()俊 措茄
			// 漂喊茄 贸府甫 窍绰霸 绝菌促.
			// 坷洒妨.. 贸府啊 救等霸 乐绢辑 巩力啊 登绰 何盒档 乐菌促.
			//  EventMorph俊辑 Zone::deletePC()俊辑 NoSuch..啊 哆绰 版快啊 乐促搁..
			// 鞠瓢 加档 巩力肺 牢秦辑 力芭
			m_Mutex.unlock();
			return; // by sigi 2002.5.2
		}

		// 窜瘤 unordered_map 狼 畴靛父阑 昏力且 挥, 农府贸 磊眉绰 昏力窍瘤 臼绰促.
		m_Creatures.erase(itr);
	} 
	//catch (Throwable & t) 
	//{
		//cerr << t.toString() << endl;
	//}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
// 农府贸 概聪历俊 甸绢乐绰 漂沥 农府贸 按眉甫 府畔茄促.
//////////////////////////////////////////////////////////////////////////////
Creature* CreatureManager::getCreature (ObjectID_t objectID) const 
{
	__BEGIN_TRY
		
	unordered_map< ObjectID_t , Creature* >::const_iterator itr = m_Creatures.find(objectID);

	if (itr == m_Creatures.end())
	{
		//throw NoSuchElementException();
		return NULL;	// by sigi 2002.5.2
	}

	return itr->second;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 农府贸 概聪历俊 甸绢乐绰 漂沥 农府贸 按眉甫 府畔茄促.
//////////////////////////////////////////////////////////////////////////////
Creature* CreatureManager::getCreature (const string& Name) const 
{
	__BEGIN_TRY
		
	unordered_map< ObjectID_t , Creature* >::const_iterator itr = find_if (m_Creatures.begin(), m_Creatures.end(), isSameNAME(Name));

	if (itr == m_Creatures.end())
	{
		//throw NoSuchElementException();
		return NULL;	// by sigi 2002.5.2
	}

	return itr->second;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 农府贸 概聪历俊 辆加等 阁胶磐/NPC 甸狼 AI俊 狼茄 咀记阑 角青茄促.
//////////////////////////////////////////////////////////////////////////////
void CreatureManager::processCreatures ()
	
{
	__BEGIN_TRY

	unordered_map< ObjectID_t , Creature* >::iterator before = m_Creatures.end();
	unordered_map< ObjectID_t , Creature* >::iterator current = m_Creatures.begin();

	Timeval currentTime;
	getCurrentTime(currentTime);

	while (current != m_Creatures.end()) 
	{
		Assert(current->second != NULL);

		if (current->second->isAlive()) 
		{
			current->second->act(currentTime);
			before = current ++;
		} 
		else 
		{
			killCreature(current->second);

			if (before == m_Creatures.end()) 
			{
				m_Creatures.erase(current);
				current = m_Creatures.begin();
			} 
			else 
			{
				m_Creatures.erase(current);
				current = before;
				current ++;
			}
		}
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 磷篮 农府贸甫 贸府茄促.
//////////////////////////////////////////////////////////////////////////////
void CreatureManager::killCreature (Creature* pDeadCreature)
	
{
	__BEGIN_TRY

	throw UnsupportedError(__PRETTY_FUNCTION__);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// broadcast packet
//////////////////////////////////////////////////////////////////////////////
void CreatureManager::broadcastPacket (Packet* pPacket , Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pPacket != NULL);

	unordered_map< ObjectID_t , Creature* >::iterator itr = m_Creatures.begin ();

	for (; itr != m_Creatures.end() ; itr ++) 
	{
		Assert(itr->second != NULL);
		Assert(itr->second->isPC());

		if (itr->second != pCreature)
		{
			Creature* pCreature = itr->second;
			Assert(pCreature != NULL);

			Player* pPlayer = pCreature->getPlayer();
			Assert(pPlayer != NULL);

			pPlayer->sendPacket(pPacket);
		}
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// broadcast DarkLight packet
//////////////////////////////////////////////////////////////////////////////
void CreatureManager::broadcastDarkLightPacket (Packet* pPacket1, Packet* pPacket2 , Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pPacket1 != NULL);
	Assert(pPacket2 != NULL);

	Creature* pTargetCreature = NULL;

	unordered_map< ObjectID_t , Creature* >::iterator itr = m_Creatures.begin ();

	for (; itr != m_Creatures.end() ; itr ++) 
	{
		Assert(itr->second != NULL);
		Assert(itr->second->isPC());

		pTargetCreature = itr->second;
		Assert(pTargetCreature != NULL);

		Zone* pZone = pTargetCreature->getZone();
		Assert(pZone != NULL);

		//ZoneCoord_t X = pTargetCreature->getX();
		//ZoneCoord_t Y = pTargetCreature->getY();

		if (pTargetCreature != pCreature) 
		{
			if (pTargetCreature->isSlayer()) 
			{
				bool bYellowPoisonEffected = pTargetCreature->isFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
				bool bLightnessEffected = pTargetCreature->isFlag(Effect::EFFECT_CLASS_LIGHTNESS);

				// 林籍贸府 by sigi
				//bool bDarknessEffected = (tile.getEffect(Effect::EFFECT_CLASS_DARKNESS) == NULL) ? false : true;

				if (!bYellowPoisonEffected && !bLightnessEffected)// && !bDarknessEffected)  // 林籍贸府 by sigi
				{
					Player* pPlayer = pTargetCreature->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(pPacket1);
				}
			} 
			else if ( pTargetCreature->isVampire() )
			{
				Player* pPlayer = pTargetCreature->getPlayer();
				pPlayer->sendPacket(pPacket2);
			}
		}
	}

	__END_CATCH
}

void CreatureManager::broadcastLevelWarBonusPacket (Packet* pPacket , Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pPacket != NULL);

	unordered_map< ObjectID_t , Creature* >::iterator itr = m_Creatures.begin ();

	for (; itr != m_Creatures.end() ; itr ++) 
	{
		Assert(itr->second != NULL);
		Assert(itr->second->isPC());

		if (itr->second != pCreature)
		{
			Creature* pCreature = itr->second;
			Assert(pCreature != NULL);

			Player* pPlayer = pCreature->getPlayer();
			Assert(pPlayer != NULL);

			if ( g_pLevelWarZoneInfoManager->isCreatureBonusZone( pCreature, pCreature->getZoneID() ) )
			{
				pPlayer->sendPacket(pPacket);
				pCreature->setFlag( Effect::EFFECT_CLASS_INIT_ALL_STAT );
			}
		}
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string CreatureManager::toString () const
	
{
	StringStream msg;
	msg << "CreatureManager(" << "Size:" << (int)m_Creatures.size();
	for (unordered_map<ObjectID_t, Creature*>::const_iterator itr = m_Creatures.begin(); itr != m_Creatures.end(); itr++)
	{
		msg << itr->second->toString();
	}
	msg << ")" ;
	return msg.toString();
}
