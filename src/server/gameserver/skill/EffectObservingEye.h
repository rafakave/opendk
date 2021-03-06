//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectObservingEye.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_OBSERVING_EYE__
#define __EFFECT_OBSERVING_EYE__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectObservingEye
//////////////////////////////////////////////////////////////////////////////

class EffectObservingEye : public Effect 
{
public:
	EffectObservingEye(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_OBSERVING_EYE; }

	void affect()  {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect(Creature* pCreature) ;
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;
	void unaffect() ; 
	void unaffect(Item* pItem)  {}

	bool canSeeInvisibility( Creature* pTarget ) const ;

	string toString() const throw();

public:
	int getDamageBonus(void) const { return m_DamageBonus; }
	void setDamageBonus(int bonus) { m_DamageBonus = bonus; }

	int getCriticalHitBonus(void) const { return m_CriticalHitBonus; }
	void setCriticalHitBonus(int bonus) { m_CriticalHitBonus = bonus; }

	int getVisionBonus(void) const { return m_VisionBonus; }
	void setVisionBonus(int bonus) { m_VisionBonus = bonus; }

	void setSkillLevel( ExpLevel_t level ) throw() { m_SkillLevel = level; }

private :
	int m_DamageBonus;
	int m_CriticalHitBonus;
	int m_VisionBonus;
	ExpLevel_t m_SkillLevel;
};

#endif // __EFFECT_OBSERVING_EYE__
