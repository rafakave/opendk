//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDoom.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectDoom.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "Player.h"
#include "GCModifyInformation.h"
#include "GCStatusCurrentHP.h"
#include "GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectDoom::EffectDoom(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDoom::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
																															    	
	__END_CATCH
}

void EffectDoom::unaffect() 
	
{
	__BEGIN_TRY	

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDoom::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectDoom" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	// 능력치를 정상적으로 되돌리기 위해서는 플래그를 끄고,
	// initAllStat을 불러야 한다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_DOOM);

	if (pCreature->isVampire())
	{
		Vampire* pTargetVampire = dynamic_cast<Vampire*>(pCreature);
		VAMPIRE_RECORD prev;

		pTargetVampire->getVampireRecord(prev);
		pTargetVampire->initAllStat();
		pTargetVampire->sendRealWearingInfo();
		pTargetVampire->sendModifyInfo(prev);
    }
	else if (pCreature->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		pMonster->initAllStat();
	}
	else if (pCreature->isSlayer())
	{
		Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pCreature);
		SLAYER_RECORD prev;

		pTargetSlayer->getSlayerRecord(prev);
		pTargetSlayer->initAllStat();
		pTargetSlayer->sendRealWearingInfo();
		pTargetSlayer->sendModifyInfo(prev);
    }
	else if (pCreature->isOusters())
	{
		Ousters* pTargetOusters = dynamic_cast<Ousters*>(pCreature);
		OUSTERS_RECORD prev;

		pTargetOusters->getOustersRecord(prev);
		pTargetOusters->initAllStat();
		pTargetOusters->sendRealWearingInfo();
		pTargetOusters->sendModifyInfo(prev);
    }
	else Assert(false);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_DOOM);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectDoom" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectDoom::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectDoom("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
