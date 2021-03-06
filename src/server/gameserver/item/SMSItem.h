//////////////////////////////////////////////////////////////////////////////
// Filename    : SMSItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SMS_ITEM_H__
#define __SMS_ITEM_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class SMSItem;
//////////////////////////////////////////////////////////////////////////////

class SMSItem : public ConcreteItem<Item::ITEM_CLASS_SMS_ITEM, NoStack, NoDurability, NoOption, NoGrade, NoAttacking, NoEnchantLevel>
{
public:
	SMSItem() ;
	SMSItem(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

private:

	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class SMSItemInfo
//////////////////////////////////////////////////////////////////////////////

class SMSItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SMS_ITEM; }
	virtual string toString() const ;

	uint	getCharge() const { return m_Charge; }
	void	setCharge( uint Charge ) { m_Charge = Charge; }

private:
	uint					m_Charge;
};

//////////////////////////////////////////////////////////////////////////////
// class SMSItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class SMSItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SMS_ITEM; }
	virtual void load() ;
};

extern SMSItemInfoManager* g_pSMSItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class SMSItemFactory
//////////////////////////////////////////////////////////////////////////////

class SMSItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SMS_ITEM; }
	virtual string getItemClassName() const  { return "SMSItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new SMSItem(ItemType,OptionType); }
};

//////////////////////////////////////////////////////////////////////////////
// class SMSItemLoader;
//////////////////////////////////////////////////////////////////////////////

class SMSItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SMS_ITEM; }
	virtual string getItemClassName() const  { return "SMSItem"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern SMSItemLoader* g_pSMSItemLoader;

#endif
