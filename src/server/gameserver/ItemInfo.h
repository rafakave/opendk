//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemInfo.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_INFO_H__
#define __ITEM_INFO_H__

#include "Types.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ItemInfo
//////////////////////////////////////////////////////////////////////////////

class ItemInfo 
{
// constructor & destructor
public:
	ItemInfo() ;
	virtual ~ItemInfo() ;


// ???? ????
public:
	virtual Item::ItemClass getItemClass() const  = 0;
	string getItemClassName() const  { return ItemClass2String[getItemClass()]; }

	ItemType_t getItemType() const  { return m_ItemType; }
    void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }
 
	string getName() const  { return m_Name; }
	void setName(const string & name)  { m_Name = name; }

	string getEName() const  { return m_EName; }
	void setEName(const string & ename)  { m_EName = ename; }
	
	Price_t getPrice() const  { return m_Price; }
	void setPrice(Price_t Price) { m_Price = Price; }

	VolumeType_t getVolumeType() const  { return m_VolumeType; }
	void setVolumeType(VolumeType_t VolumeType)  { m_VolumeType = VolumeType; }
	VolumeWidth_t getVolumeWidth() const ;
	VolumeHeight_t getVolumeHeight() const ;

	Weight_t getWeight() const  { return m_Weight; }
	void setWeight(Weight_t weight)  { m_Weight = weight; }

	Ratio_t getRatio() const  { return m_Ratio; }
	void setRatio(Ratio_t Ratio)  { m_Ratio = Ratio; }
	
	string getDescription() const  { return m_Description; }
	void setDescription(const string& description)  { m_Description = description ; }
	
	virtual Attr_t  getReqSTR(void) const     { return m_ReqSTR; }
	virtual Attr_t  getReqDEX(void) const     { return m_ReqDEX; }
	virtual Attr_t  getReqINT(void) const     { return m_ReqINT; }
	virtual Attr_t  getReqSum(void) const     { return m_ReqSum; }
	virtual Level_t getReqLevel(void) const   { return m_ReqLevel; }
	virtual Level_t getReqAdvancedLevel(void) const   { return m_ReqAdvanceLevel; }
	virtual Attr_t  getReqGender(void) const  { return m_ReqGender; }

	virtual void    setReqSTR(Attr_t req)       { m_ReqSTR = req; }
	virtual void    setReqDEX(Attr_t req)       { m_ReqDEX = req; }
	virtual void    setReqINT(Attr_t req)       { m_ReqINT = req; }
	virtual void    setReqSum(Attr_t req)       { m_ReqSum = req; }
	virtual void    setReqLevel(Level_t req)    { m_ReqLevel = req; }
	virtual void    setReqAdvanceLevel(Level_t req)    { m_ReqAdvanceLevel = req; }
	virtual void    setReqGender(Attr_t req)    { m_ReqGender = req; }
	virtual void    setReqAbility(const string& req) ;

	virtual string toString() const  = 0;


// ???? ????. ???ǻ? ???̽? Ŭ?????? ???????ش?.
public:
	virtual Durability_t getDurability() const  { return 1; }
	virtual void setDurability(Durability_t durability)  {}

	virtual Damage_t getMinDamage() const  { return 0; }
	virtual void setMinDamage(Damage_t damage)  {}

	virtual Damage_t getMaxDamage() const  { return 0; }
	virtual void setMaxDamage(Damage_t damage)  {}

	virtual Range_t getRange() const  { return 0; }
	virtual void setRange(Range_t range)  {}

	virtual ToHit_t getToHitBonus() const  { return 0; }
	virtual void setToHitBonus(ToHit_t tohit)  {}

	virtual Defense_t getDefenseBonus() const  { return 0; }
	virtual void setDefenseBonus(Defense_t defense)  {}

	virtual Protection_t getProtectionBonus() const  { return 0; }
	virtual void setProtectionBonus(Protection_t defense)  {}

	virtual MP_t getMPBonus() const  { return 0;}
	virtual void setMPBonus(MP_t bonus)  { }

	virtual Silver_t getMaxSilver() const  { return 0; }
	virtual void setMaxSilver(Silver_t amount)  { }

	virtual Speed_t getSpeed(void) const  { return 0; }
	virtual void setSpeed(Speed_t speed)  { } 

	virtual uint getItemLevel(void) const  { return 99; }
	virtual void setItemLevel(uint level)  { }

	virtual int getCriticalBonus(void) const  { return 0; }
	virtual void setCriticalBonus(int bonus)  { };

	virtual ElementalType getElementalType() const { return ELEMENTAL_MAX; }
	virtual Elemental_t getElemental() const { return 0; }
	
	// ItemType?? ???? ?⺻ ?ɼ?
	virtual void    setDefaultOptions(const string& options) ;
	void			addDefaultOptions(OptionType_t optionType) ;
	void			clearDefaultOptions() ;
	bool			hasDefaultOptions() const { return m_bDefaultOptions; }
	const list<OptionType_t>& getDefaultOptions() const { return m_DefaultOptions; }

	Ratio_t         getUpgradeRatio(void) const  { return m_UpgradeRatio; }
	void        setUpgradeRatio(Ratio_t ratio)     { m_UpgradeRatio = ratio; }
	bool 		isUpgradeSucceed() const;

	int         getUpgradeCrashPercent(void) const  { return m_UpgradeCrashPercent; }
	void        setUpgradeCrashPercent(int per)     { m_UpgradeCrashPercent = per; }
	bool 		isUpgradeCrash() const;

	int         isUnique() const  				{ return m_bUnique; }
	void        setUnique(bool bUnique=true)    { m_bUnique = bUnique; }

	Ratio_t     getNextOptionRatio(void) const  { return m_NextOptionRatio; }
	void        setNextOptionRatio(Ratio_t ratio)     { m_NextOptionRatio = ratio; }

	ItemType_t	getNextItemType() const { return m_NextItemType; }
	void		setNextItemType(ItemType_t nextItemType) { m_NextItemType = nextItemType; }

	Ratio_t		getDowngradeRatio() const { return m_DowngradeRatio; }
	void		setDowngradeRatio( Ratio_t ratio ) { m_DowngradeRatio = ratio; }

// member data
protected:
	ItemType_t   m_ItemType;     // ?????? Ÿ??
	string       m_Name;         // ?̸?
	string       m_EName;        // ???? ?̸?
	Price_t      m_Price;        // ????
	VolumeType_t m_VolumeType;   // ????
	Weight_t     m_Weight;       // ????
	Ratio_t      m_Ratio;        // ?????? ???? Ȯ??(???? Ȯ??)
	string       m_Description;  // ?????? ????
	Attr_t       m_ReqSTR;       // ?ʿ??? STR
	Attr_t       m_ReqDEX;       // ?ʿ??? DEX
	Attr_t       m_ReqINT;       // ?ʿ??? INT
	Attr_t       m_ReqSum;       // ?ʿ??? ?ɷ?ġ?? ??
	Level_t      m_ReqLevel;     // ?ʿ??? ????
	Level_t      m_ReqAdvanceLevel;// ?ʿ??? ???? ????
	Attr_t       m_ReqGender;    // ?ʿ??? ??

	bool                    m_bDefaultOptions;	// ?⺻ ?ɼ??? ?ֳ??
	list<OptionType_t>	m_DefaultOptions;	// ?⺻ ?ɼ?

	Ratio_t      m_UpgradeRatio;    		// enchant?ؼ? ?????? Ȯ??
	int          m_UpgradeCrashPercent;   // upgrade?? ?????ؼ? ?μ??? Ȯ?? = m_UpgradeCrashPercent%

	bool		 m_bUnique;		// unique item ?ΰ??

	Ratio_t      m_NextOptionRatio;    		// ?ٸ? ?ɼ??? ???? Ȯ??

	ItemType_t	 m_NextItemType;
	Ratio_t		 m_DowngradeRatio;
};

#endif	// __ITEM_INFO_H__
