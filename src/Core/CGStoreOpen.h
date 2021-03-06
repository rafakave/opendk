//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGStoreOpen.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_STORE_OPEN_H__
#define __CG_STORE_OPEN_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGStoreOpen;
//
//////////////////////////////////////////////////////////////////////

class CGStoreOpen : public Packet
{
public:
	CGStoreOpen() {};
    virtual ~CGStoreOpen() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_STORE_OPEN; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return 0; }

	// get packet name
	string getPacketName() const  { return "CGStoreOpen"; }

	// get packet's debug string
	string toString() const ;

};


//////////////////////////////////////////////////////////////////////
//
// class CGStoreOpenFactory;
//
// Factory for CGStoreOpen
//
//////////////////////////////////////////////////////////////////////

class CGStoreOpenFactory : public PacketFactory {

public:
	
	// constructor
	CGStoreOpenFactory()  {}
	
	// destructor
	virtual ~CGStoreOpenFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGStoreOpen(); }

	// get packet name
	string getPacketName() const  { return "CGStoreOpen"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_STORE_OPEN; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return 0; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGStoreOpenHandler;
//
//////////////////////////////////////////////////////////////////////

class CGStoreOpenHandler {

public:

	// execute packet's handler
	static void execute(CGStoreOpen* pCGStoreOpen, Player* pPlayer) ;

};

#endif
