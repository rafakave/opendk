//////////////////////////////////////////////////////////////////////////////
// Filename    : DistanceBlitz.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DISTANCE_BLITZ_HANDLER_H__
#define __SKILL_DISTANCE_BLITZ_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DistanceBlitz;
//////////////////////////////////////////////////////////////////////////////

class DistanceBlitz : public SkillHandler 
{
public:
	DistanceBlitz() throw() {}
	~DistanceBlitz() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "DistanceBlitz"; }
	SkillType_t getSkillType() const throw() { return SKILL_DISTANCE_BLITZ; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) ;
	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) ;

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DistanceBlitz g_DistanceBlitz;

#endif // __SKILL_DISTANCE_BLITZ_HANDLER_H__
