//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectExpansion.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_EXPANSION__
#define __EFFECT_EXPANSION__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectExpansion
//////////////////////////////////////////////////////////////////////////////

class EffectExpansion : public Effect 
{
public:
	EffectExpansion(Creature* pCreature) ;

public:
	void affect()  {}
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_EXPANSION; }

	string toString() const throw();

public:
	int getHPBonus() throw() { return m_HPBonus;}
	void setHPBonus(HP_t HPBonus)  { m_HPBonus = HPBonus;}

private :
	HP_t m_HPBonus;
};

#endif // __EFFECT_EXPANSION__
