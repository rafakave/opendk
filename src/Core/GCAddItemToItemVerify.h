//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddItemToItemVerify.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_ITEM_TO_ITEM_VERIFY_H__
#define __GC_ADD_ITEM_TO_ITEM_VERIFY_H__

#include "Packet.h"
#include "PacketFactory.h"

enum 
{
	ADD_ITEM_TO_ITEM_VERIFY_ERROR,					// error

	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE,		// enchant 완전 불가
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH,		// enchant 실패: 아이템 부서짐
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE,	// enchant 실패: 옵션 떨어짐
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK,				// enchant 성공
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE_NO_PREMIUM,	// enchant 불가 : 프리미엄 아님

	ADD_ITEM_TO_ITEM_VERIFY_TRANS_OK,
	ADD_ITEM_TO_ITEM_VERIFY_TRANS_IMPOSSIBLE,
	
	ADD_ITEM_TO_ITEM_VERIFY_MIXING_OK,
	ADD_ITEM_TO_ITEM_VERIFY_DETACHING_OK,

	ADD_ITEM_TO_ITEM_VERIFY_MIXING_FAILED_SAME_OPTION_GROUP,	// 아이템의 옵션 그룹이 같아서 섞을 수 없습니다.
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL,				// enchant 실패

	ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK,					// 펫 부활 성공

	ADD_ITEM_TO_ITEM_VERIFY_CLEAR_OPTION_OK,			// option 제거 성공
	ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK,				// grade올리기 성공

	// add by Coffee 2006.11.3
	ADD_ITEM_TO_ITEM_VERIFY_THREE_ENCHANT_OK,
	//
	ADD_ITEM_TO_ITEM_VERIFY_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddItemToItemVerify
//////////////////////////////////////////////////////////////////////////////

class GCAddItemToItemVerify : public Packet 
{

public:
	GCAddItemToItemVerify() { m_Code = ADD_ITEM_TO_ITEM_VERIFY_MAX; m_Parameter = 0;}
	virtual ~GCAddItemToItemVerify() {}

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;

	PacketID_t getPacketID() const  { return PACKET_GC_ADD_ITEM_TO_ITEM_VERIFY; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "GCAddItemToItemVerify"; }
	string toString() const ;
	
public:
	BYTE getCode(void) const  { return m_Code;}
	void setCode(BYTE code)  { m_Code = code;}

	uint getParameter(void) const  { return m_Parameter; }

	void setParameter(uint parameter)  { m_Parameter = parameter; }
	// add by Coffee 2006.11.3
	uint getParameter2(void) const  { return m_Parameter2;  }
	void setParameter2(uint parameter2)  { m_Parameter2 = parameter2; }

private: 
	BYTE m_Code;
	uint m_Parameter;
	// add by Coffee 2006.11.3  괏닸뒤랗몸橄昑
	uint m_Parameter2;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddItemToItemVerifyFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddItemToItemVerifyFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCAddItemToItemVerify(); }
	string getPacketName() const  { return "GCAddItemToItemVerify"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ADD_ITEM_TO_ITEM_VERIFY; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE + szuint +szuint; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddItemToItemVerifyHandler
//////////////////////////////////////////////////////////////////////////////

class GCAddItemToItemVerifyHandler 
{
public:
	static void execute( GCAddItemToItemVerify* pPacket, Player* pPlayer) ;
};

#endif
