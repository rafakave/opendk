//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRelicToObject.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_RELIC_TO_OBJECT_H__
#define __CG_RELIC_TO_OBJECT_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRelicToObject;
//
//////////////////////////////////////////////////////////////////////

class CGRelicToObject : public Packet {

public:
	
	// constructor
	CGRelicToObject() ;
	
	// destructor
	~CGRelicToObject() ;

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_RELIC_TO_OBJECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szObjectID + szObjectID + szCoord + szCoord; }

	// get packet name
	string getPacketName() const  { return "CGRelicToObject"; }

	// get/set Corpse's X
	Coord_t getX() const  { return m_X; }
	void setX(Coord_t X)  { m_X = X; }

	// get/set Corpse's Y
	Coord_t getY() const  { return m_Y; }
	void setY(Coord_t Y)  { m_Y = Y; }

	// get/set ObjectID
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	ObjectID_t getItemObjectID() const  { return m_ItemObjectID; }

	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }
	void setItemObjectID(ObjectID_t ItemObjectID)  { m_ItemObjectID = ItemObjectID; }

	// get packet's debug string
	string toString() const ;

private :

	ObjectID_t m_ItemObjectID;   // item object id
	ObjectID_t m_ObjectID;  // 성물보관함 object id

	Coord_t m_X;
	Coord_t m_Y;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGRelicToObjectFactory;
//
// Factory for CGRelicToObject
//
//////////////////////////////////////////////////////////////////////

class CGRelicToObjectFactory : public PacketFactory {

public:
	
	// constructor
	CGRelicToObjectFactory()  {}
	
	// destructor
	virtual ~CGRelicToObjectFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGRelicToObject(); }

	// get packet name
	string getPacketName() const  { return "CGRelicToObject"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_RELIC_TO_OBJECT; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szObjectID + szCoord + szCoord; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGRelicToObjectHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRelicToObjectHandler {

public:

	// execute packet's handler
	static void execute(CGRelicToObject* pCGRelicToObject, Player* pPlayer) ;

private :
	static void executeRelic(CGRelicToObject* pCGRelicToObject, Player* pPlayer) ;
	static void executeBloodBible(CGRelicToObject* pCGRelicToObject, Player* pPlayer) ;
	static void executeCastleSymbol(CGRelicToObject* pCGRelicToObject, Player* pPlayer) ;
	static void executeFlag(CGRelicToObject* pCGRelicToObject, Player* pPlayer) ;
	static void executeSweeper(CGRelicToObject* pCGRelicToObject, Player* pPlayer) ;

};

#endif
