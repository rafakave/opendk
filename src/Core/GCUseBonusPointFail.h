//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUseBonusPointFail.h 
// Written By  : crazydog
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_USE_BONUS_POINT_FAIL_H__
#define __GC_USE_BONUS_POINT_FAIL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCUseBonusPointFail;
//
//////////////////////////////////////////////////////////////////////

class GCUseBonusPointFail : public Packet {

public :

	// constructor
	GCUseBonusPointFail()  {}
    ~GCUseBonusPointFail() {};
	

public :

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_USE_BONUS_POINT_FAIL; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return 0; }
	
	// get packet's name
	string getPacketName() const  { return "GCUseBonusPointFail"; }
	
	// get packet's debug string
	string toString() const ;
	

public :


private : 


};


//////////////////////////////////////////////////////////////////////
//
// class  GCUseBonusPointFailFactory;
//
// Factory for  GCUseBonusPointFail
//
//////////////////////////////////////////////////////////////////////

class  GCUseBonusPointFailFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCUseBonusPointFail(); }

	// get packet name
	string getPacketName() const  { return "GCUseBonusPointFail"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_USE_BONUS_POINT_FAIL; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCUseBonusPointFailHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCUseBonusPointFailHandler {

public :

	// execute packet's handler
	static void execute(GCUseBonusPointFail* pPacket, Player* pPlayer) ;

};

#endif
