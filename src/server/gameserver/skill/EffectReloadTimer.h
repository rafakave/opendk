//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectReloadTimer.h
// Written by  : crazydog
// Description : 탄창 reload dealy를 위한 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RELOAD_TIMER__
#define __EFFECT_RELOAD_TIMER__

#include "Effect.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectReloadTimer
//////////////////////////////////////////////////////////////////////////////

class EffectReloadTimer : public Effect 
{
public:
	EffectReloadTimer(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_RELOAD_TIMER; }

	void affect() {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;
	
	void unaffect(Creature* pCreature) ;
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;
	void unaffect(Item* pItem)  {}
	void unaffect() ;

	string toString() const throw();

public:
	void setFromInventory(bool b) throw() { m_bFromInventory = b; }
	void setSlotID(SlotID_t id)  { m_SlotID = id; }
	void setObjectID(ObjectID_t id)  { m_ObjectID = id; }
	void setInventoryXY(CoordInven_t x, CoordInven_t y) throw() { m_invenX = x; m_invenY = y; }

private:
	CoordInven_t m_invenX;         // 인벤토리에서 리로드할 때의 좌표
	CoordInven_t m_invenY;         // 인벤토리에서 리로드할 때의 좌표
	ObjectID_t   m_ObjectID;       // 탄창 object id
	SlotID_t     m_SlotID;         // 벨트에서 리로드할 때의 벨트 slot id
	bool         m_bFromInventory; // 인벤토리에서 직접 리로드하는가?

};


#endif // __EFFECT_RELOAD_TIMER__
