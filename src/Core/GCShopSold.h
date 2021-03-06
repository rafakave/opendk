//--------------------------------------------------------------------------------
// 
// Filename    : GCShopSold.h 
// Written By  : 김성민
// Description : 한 플레이어가 상점 NPC에게 물건을 구입했는데,
//               다른 플레이어도 같은 상점 NPC와 대화 중이었다면,
//               그 플레이어와 아이템 목록을 동기화시켜주어야 한다.
//               이 패킷은 그를 위한 패킷이다.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SHOP_SOLD_H__
#define __GC_SHOP_SOLD_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCShopSold;
//
//--------------------------------------------------------------------------------

class GCShopSold : public Packet 
{

public :

	GCShopSold() ;
	virtual ~GCShopSold() ;
	
	// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
	void read(SocketInputStream & iStream) ;
		    
	// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
	void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_SHOP_SOLD; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szObjectID + szShopVersion + szShopRackType + szBYTE;}

	// get packet name
	string getPacketName() const  { return "GCShopSold"; }
	
	// get packet's debug string
	string toString() const ;


public :

	// get/set NPC's object id
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	// get/set shop version	
	ShopVersion_t getShopVersion(void) const  { return m_Version;}
	void setShopVersion(const ShopVersion_t ver)  { m_Version = ver;}

	// get/set rack type
	ShopRackType_t getShopType(void) const  { return m_RackType;}
	void setShopType(ShopRackType_t type)  { m_RackType = type;}
	
	// get/set rack index
	BYTE getShopIndex(void) const  { return m_RackIndex;}
	void setShopIndex(BYTE index)  { m_RackIndex = index;}

private :
	
	// NPC's object id
	ObjectID_t m_ObjectID;
	
	// 상점 버젼
	ShopVersion_t m_Version;

	// 진열장 종류	
	ShopRackType_t m_RackType;
	
	// 진열장 인덱스
	BYTE m_RackIndex;
	
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSoldFactory;
//
// Factory for GCShopSold
//
//////////////////////////////////////////////////////////////////////

class GCShopSoldFactory : public PacketFactory 
{

public :
	
	// create packet
	Packet* createPacket()  { return new GCShopSold(); }

	// get packet name
	string getPacketName() const  { return "GCShopSold"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SHOP_SOLD; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCShopSoldPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szShopVersion + szShopRackType + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSoldHandler;
//
//////////////////////////////////////////////////////////////////////

class GCShopSoldHandler 
{
	
public :
	
	// execute packet's handler
	static void execute(GCShopSold* pPacket, Player* pPlayer) ;

};

#endif
