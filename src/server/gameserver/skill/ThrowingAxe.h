//////////////////////////////////////////////////////////////////////////////
// Filename    : ThrowingAxe.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_THROWING_AXE_HANDLER_H__
#define __SKILL_THROWING_AXE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ThrowingAxe;
//////////////////////////////////////////////////////////////////////////////

class ThrowingAxe : public SkillHandler 
{
public:
	ThrowingAxe() throw() {}
	~ThrowingAxe() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ThrowingAxe"; }
	SkillType_t getSkillType() const throw() { return SKILL_THROWING_AXE; }

	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y) ;

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ThrowingAxe g_ThrowingAxe;

#endif // __SKILL_THROWING_AXE_HANDLER_H__
