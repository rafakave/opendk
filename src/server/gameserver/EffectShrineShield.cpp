//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShrineShield.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectShrineShield.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "MonsterCorpse.h"
#include "Player.h"
#include "ZoneGroupManager.h"
#include "GCModifyInformation.h"
#include "GCStatusCurrentHP.h"
#include "GCAddEffect.h"
#include "GCRemoveEffect.h"
#include "GCSystemMessage.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectShrineShield::EffectShrineShield(Creature* pCreature)
	
{
	__BEGIN_TRY

	m_ShrineID = 0;
	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectShrineShield::EffectShrineShield(Item* pItem)
	
{
	__BEGIN_TRY

	setTarget(pItem);

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectShrineShield::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectShrineShield::affect(Item* pItem)
	
{
	__BEGIN_TRY

	__END_CATCH
}


void EffectShrineShield::unaffect() 
	
{
	__BEGIN_TRY	

	
	switch (m_pTarget->getObjectClass())
	{
		case OBJECT_CLASS_CREATURE :
		{
			Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
			unaffect(pCreature);
		}
		break;

		case OBJECT_CLASS_ITEM :
		{
			Item* pItem = dynamic_cast<Item *>(m_pTarget);
			unaffect(pItem);
		}
		break;

		default :
			throw Error("Wrong Object Class");
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectShrineShield::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectShrineShield" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	// ???????? ?????????? ???????? ???????? ???????? ????,
	// initAllStat?? ?????? ????.
	pCreature->removeFlag(Effect::EFFECT_CLASS_SHRINE_SHIELD);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_SHRINE_SHIELD);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectShrineShield" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectShrineShield::unaffect(Item* pItem)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectShrineShield" << "unaffect BEGIN" << endl;

	Assert(pItem != NULL);

	Assert(pItem->getItemClass()==Item::ITEM_CLASS_CORPSE);
	Assert(pItem->getItemType()==MONSTER_CORPSE);

	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pItem);

	pCorpse->removeFlag(Effect::EFFECT_CLASS_SHRINE_SHIELD);

	Zone* pZone = pCorpse->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pItem->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_SHRINE_SHIELD);
	pZone->broadcastPacket(pCorpse->getX(), pCorpse->getY(), &gcRemoveEffect);

	//cout << "EffectShrineShield" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectShrineShield::toString()
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectShrineShield("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
