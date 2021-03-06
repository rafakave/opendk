//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHolyArmor.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HOLY_ARMOR__
#define __EFFECT_HOLY_ARMOR__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHolyArmor
//////////////////////////////////////////////////////////////////////////////

class EffectHolyArmor : public Effect 
{
public:
	EffectHolyArmor(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_HOLY_ARMOR; }

	void affect()  {}
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

	string toString() const throw();

public:
	int getDefBonus() throw() { return m_DefBonus;}
	void setDefBonus(Attr_t DefBonus)  { m_DefBonus = DefBonus;}

private :
	Defense_t m_DefBonus;
};

#endif // __EFFECT_HOLY_ARMOR__
