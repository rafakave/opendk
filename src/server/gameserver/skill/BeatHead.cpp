//////////////////////////////////////////////////////////////////////////////
// Filename    : BeatHead.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BeatHead.h"
#include "SimpleMissileSkill.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BeatHead::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(vampire)" << endl;

	SkillInput input(pOusters, pOustersSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_OUSTERS_WRISTLET;
	param.STRMultiplier = 0;
	param.DEXMultiplier = 0;
	param.INTMultiplier = 0;
	param.bMagicHitRoll = true;
	param.bMagicDamage  = true;
	param.bAdd          = false;

	if ( input.SkillLevel < 15 ) param.Grade = 0;
	else if ( input.SkillLevel < 30 ) param.Grade = 1;
	else param.Grade = 2;

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleMissileSkill.execute(pOusters, TargetObjectID, pOustersSkillSlot, param, result, CEffectID);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;

	__END_CATCH
}

BeatHead g_BeatHead;

