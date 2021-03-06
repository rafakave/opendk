////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSimpleQuestComplete.cpp
// Written By  : excel96
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionSimpleQuestComplete.h"
#include "Creature.h"
#include "GamePlayer.h"
#include "Script.h"
#include "ScriptManager.h"

#include "GCNPCAskDynamic.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionSimpleQuestComplete::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		// read script id
		//m_ScriptID = propertyBuffer.getPropertyInt("ScriptID");
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
void ActionSimpleQuestComplete::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

/*	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	const Script* pScript = g_pPublicScriptManager->getScript(m_ScriptID);

	GCNPCAskDynamic gcNPCAskDynamic;
	gcNPCAskDynamic.setObjectID(pCreature1->getObjectID());
	gcNPCAskDynamic.setScriptID(m_ScriptID);
	gcNPCAskDynamic.setSubject(pScript->getSubject(0));

	for (uint c=0; c<pScript->getContentCount(); c++)
	{
		gcNPCAskDynamic.addContent(pScript->getContent(c));
	}

	Player* pPlayer = pCreature2->getPlayer();
	pPlayer->sendPacket(&gcNPCAskDynamic);*/

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSimpleQuestComplete::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionSimpleQuestComplete("
	    << ",ScriptID:"  << (int)m_ScriptID
	    << ")";

	return msg.toString();

	__END_CATCH
}
