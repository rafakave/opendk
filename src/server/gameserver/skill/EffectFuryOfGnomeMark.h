
//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectFuryOfGnomeMark.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 FuryOfGnomeMark의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_FURY_OF_GNOME_MARK__
#define __EFFECT_FURY_OF_GNOME_MARK__

#include "Effect.h"
#include "EffectLoader.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectFuryOfGnomeMark
//////////////////////////////////////////////////////////////////////////////

class EffectFuryOfGnomeMark : public Effect 
{
public:
	EffectFuryOfGnomeMark(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_FURY_OF_GNOME_MARK; }

	void affect() ;
	void affect(Creature* pCreature) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;

	string toString() const throw();

public:
	string getCasterName(void) const { return m_CasterName; }
	void setCasterName(const string& CasterName ) { m_CasterName = CasterName; }

	ObjectID_t getCasterID(void) const { return m_CasterID; }
	void setCasterID(ObjectID_t CasterID ) { m_CasterID = CasterID; }


private:
	string m_CasterName;
	ObjectID_t  m_CasterID;

};



#endif // __EFFECT_FURY_OF_GNOME_MARK__
