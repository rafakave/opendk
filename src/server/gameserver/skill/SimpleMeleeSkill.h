//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleMeleeSkill.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SIMPLEMELEESKILL__
#define __SIMPLEMELEESKILL__

#include "SimpleSkill.h"

class SimpleMeleeSkill
{
public:
	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, 
		const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0) ;
	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, 
		const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0, int HitBonus=0) ;
	void execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pOustersSkillSlot, 
		const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0, int HitBonus=0) ;
	void execute(Monster* pMonster, Creature* pEnemy, 
		const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0) ;
};

extern SimpleMeleeSkill g_SimpleMeleeSkill;

#endif
