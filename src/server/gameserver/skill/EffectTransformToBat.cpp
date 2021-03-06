//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTransformToBat.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectTransformToBat.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "GCModifyInformation.h"
#include "GCAddVampireFromTransformation.h"
#include "GCAddMonsterFromTransformation.h"
#include "GCDeleteObject.h"
#include "ZoneUtil.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectTransformToBat::EffectTransformToBat(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToBat::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToBat::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToBat::unaffect() 
	
{
	__BEGIN_TRY	

	//cout << "EffectTransformToBat " << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	Assert(pCreature != NULL);

	if (pCreature->isSlayer())
	{
		//cout << "EffectTransfromToWolf::unaffect() : Slayer cannot transfrom to bat!" << endl;
		throw Error("EffectTransfromToWolf::unaffect() : Slayer cannot transfrom to bat!");
	}

	unaffect(pCreature);

	//cout << "EffectTransformToBat " << "unaffect BEGIN" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToBat::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectTransformToBat " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ???? ???????? ????????, ???????? ????????.
	addUntransformCreature(pZone, pCreature, false);
	pCreature->removeFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT);

	// ???????? ???????? ????????.
	if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		VAMPIRE_RECORD prev;
	
		pVampire->getVampireRecord(prev);
		pVampire->initAllStat();
		pVampire->sendRealWearingInfo();
		pVampire->sendModifyInfo(prev);
	}
	else if (pCreature->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		pMonster->initAllStat();
	}
	else
	{
		Assert(false);
	}

	//cout << "EffectTransformToBat " << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToBat::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectTransformToBat::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectTransformToBat("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH
}
