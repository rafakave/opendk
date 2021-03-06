//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBless.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BLESS__
#define __EFFECT_BLESS__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBless
//////////////////////////////////////////////////////////////////////////////

class EffectBless : public Effect 
{
public:
	EffectBless(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BLESS; }

	void affect()  {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect(Creature* pCreature) ;
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;
	void unaffect() ; 
	void unaffect(Item* pItem)  {}

	string toString() const throw();

public:
	int getSTRBonus(void) const { return m_STRBonus; }
	void setSTRBonus(int bonus) { m_STRBonus = bonus; }

	int getDEXBonus(void) const { return m_DEXBonus; }
	void setDEXBonus(int bonus) { m_DEXBonus = bonus; }

private :
	int m_STRBonus;
	int m_DEXBonus;
};

#endif // __EFFECT_BLESS__
