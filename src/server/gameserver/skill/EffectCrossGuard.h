//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCrossGuard.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CROSS_GUARD__
#define __EFFECT_CROSS_GUARD__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectCrossGuard
//////////////////////////////////////////////////////////////////////////////

class EffectCrossGuard : public Effect 
{
public:
	EffectCrossGuard(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_CROSS_GUARD; }

	void affect() {}

	void unaffect(Creature* pCreature) ;
	void unaffect() ;

	string toString() const throw();

public:
	void setBonus( uint bonus ) { m_Bonus = bonus; }
	uint getBonus() const { return m_Bonus; }

private:
	uint	m_Bonus;
};

#endif // __EFFECT_CROSS_GUARD__
