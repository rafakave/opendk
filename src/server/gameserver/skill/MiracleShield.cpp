//////////////////////////////////////////////////////////////////////////////
// Filename    : MiracleShield.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MiracleShield.h"
#include "EffectMiracleShield.h"
#include "GCSkillToSelfOK1.h"
#include "GCSkillToSelfOK2.h"
#include "GCStatusCurrentHP.h"
#include "GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void MiracleShield::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// 무장하고 있는 무기가 널이거나, 도가 아니라면 사용할 수 없다.
		Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pItem == NULL || pItem->getItemClass() != Item::ITEM_CLASS_SWORD)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		ZoneCoord_t X = pSlayer->getX();
		ZoneCoord_t Y = pSlayer->getY();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP(); 
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bEffected   = pSlayer->isFlag(Effect::EFFECT_CLASS_MIRACLE_SHIELD);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// 이펙트 클래스를 만들어 붙인다.
			EffectMiracleShield* pEffect = new EffectMiracleShield(pSlayer);
			pEffect->setDeadline(output.Duration);
			pEffect->setDefenseBonus(output.Damage);
			pEffect->setProtectionBonus(output.Damage);
			pSlayer->addEffect(pEffect);
			pSlayer->setFlag(Effect::EFFECT_CLASS_MIRACLE_SHIELD);

			// 이로 인하여 바뀌는 능력치를 보낸다.
			SLAYER_RECORD prev;
			pSlayer->getSlayerRecord(prev);
			pSlayer->initAllStat();
			pSlayer->sendRealWearingInfo();
			pSlayer->sendModifyInfo(prev);

			// 경험치를 올린다.
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10*(Grade+1);
			shareAttrExp(pSlayer, ExpUp, 8, 1, 1, _GCSkillToSelfOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(output.Duration);
		
			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(output.Duration);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(X, Y, &_GCSkillToSelfOK2, pSlayer);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pSlayer->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_MIRACLE_SHIELD);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddEffect);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

MiracleShield g_MiracleShield;
