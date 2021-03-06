//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDivineSpirits.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DIVINE_SPIRITS__
#define __EFFECT_DIVINE_SPIRITS__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDivineSpirits
//////////////////////////////////////////////////////////////////////////////

class EffectDivineSpirits : public Effect 
{
public:
	EffectDivineSpirits(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DIVINE_SPIRITS; }

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

#endif // __EFFECT_DIVINE_SPIRITS__
