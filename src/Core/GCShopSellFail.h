//--------------------------------------------------------------------------------
// 
// Filename    : GCShopSellFail.h 
// Written By  : 김성민
// Description : 플레이어가 NPC에게 물건을 팔려고 했는데, 어떤 이유로 
//               실패했을 경우에는 이 패킷을 플레이어에게 보내준다.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SHOP_SELL_FAIL_H__
#define __GC_SHOP_SELL_FAIL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCShopSellFail;
//
//--------------------------------------------------------------------------------

class GCShopSellFail : public Packet 
{

public :

	GCShopSellFail() ;
	virtual ~GCShopSellFail() ;
	
	// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
	void read(SocketInputStream & iStream) ;
		    
	// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
	void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_SHOP_SELL_FAIL; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szObjectID;}

	// get packet name
	string getPacketName() const  { return "GCShopSellFail"; }
	
	// get packet's debug string
	string toString() const ;


public :

	// get/set NPC's object id
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }


private :
	
	// NPC's object id
	ObjectID_t m_ObjectID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSellFailFactory;
//
// Factory for GCShopSellFail
//
//////////////////////////////////////////////////////////////////////

class GCShopSellFailFactory : public PacketFactory 
{

public :
	
	// create packet
	Packet* createPacket()  { return new GCShopSellFail(); }

	// get packet name
	string getPacketName() const  { return "GCShopSellFail"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SHOP_SELL_FAIL; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCShopSellFailPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSellFailHandler;
//
//////////////////////////////////////////////////////////////////////

class GCShopSellFailHandler 
{
	
public :
	
	// execute packet's handler
	static void execute(GCShopSellFail* pPacket, Player* pPlayer) ;

};

#endif
