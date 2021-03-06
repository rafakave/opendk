//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDeath.h
// Written by  : 
// Description : Death에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DEATH__
#define __EFFECT_DEATH__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDeath
//////////////////////////////////////////////////////////////////////////////

class EffectDeath : public Effect 
{
public:
	EffectDeath(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DEATH; }

	void affect()  {}
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

	string toString() const throw();

public:
	int  getLevel() const { return m_Level; }
	void setLevel(int level) throw() { m_Level = level; }

	int getResistPenalty(void) const { return m_ResistPenalty; }
	void setResistPenalty(int penalty) { m_ResistPenalty = penalty; }

private:
	int m_Level;
	int m_ResistPenalty;
};

#endif // __EFFECT_DEATH__
