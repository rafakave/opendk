//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireCorpse.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __VAMPIRE_CORPSE_H__
#define __VAMPIRE_CORPSE_H__

#include "Item.h"
#include "ItemFactory.h"
#include "Corpse.h"
#include "PCVampireInfo3.h"

class Vampire;

//////////////////////////////////////////////////////////////////////////////
// class VampireCorpse;
// 뱀파이어가 죽었을 경우, 남기는 시체이다.
//////////////////////////////////////////////////////////////////////////////

class VampireCorpse : public Corpse 
{
public:
	VampireCorpse(Vampire* pVampire) ;
	virtual ~VampireCorpse() ;

public:
	virtual void create(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y, ItemID_t itemID=0)  {}
	virtual bool destroy()  { return true; }
	virtual void save(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y)  {}
	void tinysave(const string & field) const  { tinysave(field.c_str()); }
    void tinysave(const char* field) const  {}


public:
	virtual ItemClass getItemClass() const  { return ITEM_CLASS_CORPSE; }

	virtual ItemType_t getItemType() const  { return VAMPIRE_CORPSE; }
	virtual void setItemType(ItemType_t itemType)  { throw UnsupportedError(__PRETTY_FUNCTION__); }

	virtual string toString() const ;

public:
	PCVampireInfo3 & getVampireInfo()  { return m_VampireInfo; }
	const PCVampireInfo3 & getVampireInfo() const  { return m_VampireInfo; }
	void setVampireInfo(const PCVampireInfo3 & slayerInfo)  { m_VampireInfo = slayerInfo; }

	void setXY(ZoneCoord_t X, ZoneCoord_t Y) { m_VampireInfo.setX(X); m_VampireInfo.setY(Y); }

protected:
	PCVampireInfo3 m_VampireInfo; // 시체의 외모에 대한 정보
};

#endif
