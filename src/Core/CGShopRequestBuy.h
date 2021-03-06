////////////////////////////////////////////////////////////////////////////////
// Filename    : CGShopRequestBuy.h 
// Written By  : 김성민
// Description : 
// 플레이어가 상점 NPC의 진열창을 보고, 물건을 구입하고자 할 때
// 보내는 패킷이다. 서버는 플레이어에게 충분한 돈과 인벤토리에 
// 자리가 있는지 검증한 후, 플레이어에게 아이템을 넘긴다.
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_SHOP_REQUEST_BUY_H__
#define __CG_SHOP_REQUEST_BUY_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGShopRequestBuy;
//
////////////////////////////////////////////////////////////////////////////////

class CGShopRequestBuy : public Packet 
{
public:
    CGShopRequestBuy() {};
    virtual ~CGShopRequestBuy() {};
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_SHOP_REQUEST_BUY; }
	PacketSize_t getPacketSize() const  { return szObjectID+szShopRackType+szBYTE+szItemNum+szCoord*2; }
	string getPacketName() const  { return "CGShopRequestBuy"; }
	string toString() const ;
	
public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	ShopRackType_t getShopType(void) const  { return m_RackType; }
	void setShopType(ShopRackType_t type)  { m_RackType = type; }
	
	BYTE getShopIndex(void) const  { return m_RackIndex; }
	void setShopIndex(BYTE index)  { m_RackIndex = index;}

	ItemNum_t getItemNum(void) const  { return m_Num;}
	void setItemNum(ItemNum_t num)  { m_Num = num;}

	Coord_t getX(void) const  { return m_X; }
	void setX(Coord_t x)  { m_X = x;}

	Coord_t getY(void) const  { return m_Y; }
	void setY(Coord_t y)  { m_Y = y;}

private:
	ObjectID_t     m_ObjectID;  // NPC ID
	ShopRackType_t m_RackType;  // Rack type
	BYTE           m_RackIndex; // Rack index
	ItemNum_t      m_Num;       // Number of item
	Coord_t        m_X;         // 플레이어 인벤토리 내의 좌표값
	Coord_t        m_Y; 

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGShopRequestBuyFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGShopRequestBuyFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGShopRequestBuy(); }
	string getPacketName() const  { return "CGShopRequestBuy"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_SHOP_REQUEST_BUY; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID+szShopRackType+szBYTE+szItemNum+szCoord*2; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGShopRequestBuyHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGShopRequestBuyHandler 
{
public:
	static void execute(CGShopRequestBuy* pPacket, Player* player) ;
	static void executeNormal(CGShopRequestBuy* pPacket, Player* player) ;
	static void executeMotorcycle(CGShopRequestBuy* pPacket, Player* player) ;
	static void executeEvent(CGShopRequestBuy* pPacket, Player* player) ;
};

#endif
