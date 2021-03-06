//////////////////////////////////////////////////////////////////////////////
// Filename    : PotentialExplosion.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "PotentialExplosion.h"
#include "EffectPotentialExplosion.h"
#include "PacketUtil.h"

#include "GCSkillToSelfOK1.h"
#include "GCSkillToSelfOK2.h"
#include "GCAddEffect.h"
#include "GCOtherModifyInfo.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void PotentialExplosion::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	SkillType_t       SkillType  = pSkillSlot->getSkillType();
	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// 무장하고 있는 무기가 널이거나, 도가 아니라면 사용할 수 없다.
		Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pItem == NULL || pItem->getItemClass() != Item::ITEM_CLASS_BLADE)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		ZoneCoord_t X     = pSlayer->getX();
		ZoneCoord_t Y     = pSlayer->getY();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bEffected   = pSlayer->isFlag(Effect::EFFECT_CLASS_POTENTIAL_EXPLOSION);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// HP가 반보다 작을 때는 약간 더 올라간다.
			// by sigi. 2002.12.3
			if (pSlayer->getHP(ATTR_CURRENT) < (pSlayer->getHP(ATTR_MAX)/2))
			{
				//output.Damage += 4;
				output.Damage = 8 + input.SkillLevel/15;
			}
			else
			{
				output.Damage = 3 + input.SkillLevel/20;
			}

			int diffSTR  = output.Damage;
			int diffDEX  = output.Damage;

			EffectPotentialExplosion* pEffect = new EffectPotentialExplosion(pSlayer);
			pEffect->setDeadline(output.Duration);
			pEffect->setDiffSTR(diffSTR);
			pEffect->setDiffDEX(diffDEX);
			pSlayer->addEffect(pEffect);
			pSlayer->setFlag(Effect::EFFECT_CLASS_POTENTIAL_EXPLOSION);

			// 이로 인하여 바뀌는 능력치를 보낸다.
			SLAYER_RECORD prev;
			pSlayer->getSlayerRecord(prev);
			pSlayer->initAllStat();
			pSlayer->sendRealWearingInfo();
			pSlayer->sendModifyInfo(prev);

			// 경험치를 올려준다.
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10*(Grade+1);
			shareAttrExp(pSlayer, ExpUp, 8, 1, 1, _GCSkillToSelfOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1);
			//increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);

			// 패킷을 보내준다.
			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(output.Duration);
		
			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(output.Duration);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(X, Y, &_GCSkillToSelfOK2, pSlayer);

			// 이펙트가 붙었다고 알려준다.
			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pSlayer->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_POTENTIAL_EXPLOSION);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddEffect);

			GCOtherModifyInfo gcOtherModifyInfo;
			makeGCOtherModifyInfo(&gcOtherModifyInfo, pSlayer, &prev);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcOtherModifyInfo, pSlayer);

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

PotentialExplosion g_PotentialExplosion;
