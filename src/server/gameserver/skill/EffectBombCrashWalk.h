//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBombCrashWalk.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 BombCrashWalk의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BOMB_CRASH_WALK__
#define __EFFECT_BOMB_CRASH_WALK__

#include "Effect.h"
#include "EffectLoader.h"
#include "HitRoll.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBombCrashWalk
//////////////////////////////////////////////////////////////////////////////

class EffectBombCrashWalk : public Effect 
{
public:
	EffectBombCrashWalk(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SKILL_BOMB_CRASH_WALK_TO_ENEMY; }

	void affect() ;
	void affect(Creature* pCreature) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;

	string toString() const throw();

public:
	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	ObjectID_t getUserObjectID(void) const { return m_UserObjectID; }
	void setUserObjectID(ObjectID_t UserObjectID ) { m_UserObjectID = UserObjectID; }

	SkillType_t getSkillType() const { return m_SkillType; }
	void setSkillType( SkillType_t skillType ) { m_SkillType = skillType; }

	int getStormTime() const { return m_StormTime; }
	void setStormTime( int stormTime ) { m_StormTime = stormTime; }

	Turn_t getTick() const { return m_Tick; }
	void setTick( Turn_t tick ) { m_Tick = tick; }

	bool isLarge() const { return m_bLarge; }
	void setLarge( bool large ) { m_bLarge = large; }

private:
	int			m_Damage;
	ObjectID_t	m_UserObjectID;
	SkillType_t	m_SkillType;
	int			m_StormTime;			// 데미지를 몇 번 가하는가?
	Turn_t		m_Tick;					// 몇 턴 간격으로 떨어지는가?
	bool		m_bLarge;				// true 면 5x5 false면 3x3
};

#endif // __EFFECT_BOMB_CRASH_WALK__
