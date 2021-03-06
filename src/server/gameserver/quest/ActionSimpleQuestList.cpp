////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSimpleQuestList.cpp
// Written By  : excel96
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionSimpleQuestList.h"
#include "Creature.h"
#include "GamePlayer.h"
#include "Script.h"
#include "ScriptManager.h"
//#include "Quest.h"
#include "NPC.h"
#include "GCNPCAskDynamic.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionSimpleQuestList::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_ScriptID = propertyBuffer.getPropertyInt("ScriptID");
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionSimpleQuestList::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

/*#ifdef __ACTIVE_QUEST__
	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);

	// m_ScriptID와 관련된 정보를 PublicScriptManager에 생성
	Script* pScript = g_pPublicScriptManager->getScript(m_ScriptID);

	pNPC->setSimpleQuestListScript( pScript );

	// 패킷 보냄
	GCNPCAskDynamic gcNPCAskDynamic;
	gcNPCAskDynamic.setObjectID(pCreature1->getObjectID());
	gcNPCAskDynamic.setScriptID(m_ScriptID);
	gcNPCAskDynamic.setSubject(pScript->getSubject(0));

	for (uint c=0; c<pScript->getContentCount(); c++)
	{
		gcNPCAskDynamic.addContent(pScript->getContent(c));
	}

	Player* pPlayer = pCreature2->getPlayer();
	pPlayer->sendPacket(&gcNPCAskDynamic);

	
#endif*/

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSimpleQuestList::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionSimpleQuestList("
	    << ")";

	return msg.toString();

	__END_CATCH
}

