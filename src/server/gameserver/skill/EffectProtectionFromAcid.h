//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectProtectionFromAcid.h
// Written by  : excel96
// Description : 
// ProtectionFromAcid에 의해서 생성되는 산성 데미지 약화 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PROTECTION_FROM_ACID__
#define __EFFECT_PROTECTION_FROM_ACID__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectProtectionFromAcid
//////////////////////////////////////////////////////////////////////////////

class EffectProtectionFromAcid : public Effect 
{
public:
	EffectProtectionFromAcid(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_PROTECTION_FROM_ACID; }

	void affect() {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;
	void unaffect(Item* pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	string toString() const throw();

public:
	Resist_t getResist(void) const throw() { return m_Resist; }
	void setResist(Resist_t resist) { m_Resist = resist; }

private :
	Resist_t m_Resist;

};

//////////////////////////////////////////////////////////////////////////////
// class EffectProtectionFromAcidLoader
//////////////////////////////////////////////////////////////////////////////

class EffectProtectionFromAcidLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_PROTECTION_FROM_ACID; }
	virtual string getEffectClassName() const throw() { return "EffectProtectionFromAcid"; }

public:
	virtual void load(Creature* pCreature) ;
};

extern EffectProtectionFromAcidLoader* g_pEffectProtectionFromAcidLoader;

#endif // __EFFECT_PROTECTION_FROM_ACID__
