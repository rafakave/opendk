//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemInfoManager.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_INFO_MANAGER_H__
#define __ITEM_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// Class ItemInfoManager
//////////////////////////////////////////////////////////////////////////////

class ItemInfoManager 
{
public:
	ItemInfoManager() ;
	~ItemInfoManager() ;

public:
	void init() ;
	InfoClassManager* getInfoManager(Item::ItemClass Class) const ;
	ItemInfo* getItemInfo(Item::ItemClass Class, ItemType_t ItemType) const ;
	uint getItemCount(Item::ItemClass Class) const ;

	vector<ItemType_t> getPossibleItemTypes(Item::ItemClass IClass, uint minLevel, uint maxLevel) ;

	bool isPossibleItem(Item::ItemClass IClass, ItemType_t IType, const list<OptionType_t>& OType) ;

	uint getItemIDSuccessor(void) const { return m_ItemIDSuccessor; }
	void setItemIDSuccessor(uint suc) { m_ItemIDSuccessor = suc; }

	uint getItemIDBase(void) const { return m_ItemIDBase; }
	void setItemIDBase(uint base) { m_ItemIDBase = base; }

	string toString() const ;

private:
	InfoClassManager* m_InfoClassManagers[Item::ITEM_CLASS_MAX];

	uint m_ItemIDSuccessor; // ItemID를 발급받을 때의 증가치(서버의 숫자)
	uint m_ItemIDBase;      // 각 서버마다 다른 베이스
};

extern ItemInfoManager* g_pItemInfoManager;

#endif
