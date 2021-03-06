//////////////////////////////////////////////////////////////////////////////
// Filename    : Piercing.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PIERCING_HANDLER_H__
#define __SKILL_PIERCING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Piercing;
//////////////////////////////////////////////////////////////////////////////

class Piercing : public SkillHandler 
{
public:
	Piercing() throw() {}
	~Piercing() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Piercing"; }
	SkillType_t getSkillType() const throw() { return SKILL_PIERCING; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) ;
	void execute(Slayer* pSlayer, ObjectID_t targetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) ;

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Piercing g_Piercing;

#endif // __SKILL_PIERCING_H__
