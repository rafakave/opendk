//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCVersionCheckOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_VERSION_CHECK_OK_H__
#define __LC_VERSION_CHECK_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCVersionCheckOK;
//
// 로그인서버가 클라이언트에게 로그인 성공을 알려주는 패킷이다.
//
//////////////////////////////////////////////////////////////////////

class LCVersionCheckOK : public Packet {

public:
    LCVersionCheckOK() {};
    virtual ~LCVersionCheckOK() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_LC_VERSION_CHECK_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static LCVersionCheckOKPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize() const  { return 0; }
	
	// get packet's name
	string getPacketName() const  { return "LCVersionCheckOK"; }
	
	// get packet's debug string
	string toString() const  { return "LCVersionCheckOK"; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCVersionCheckOKFactory;
//
// Factory for LCVersionCheckOK
//
//////////////////////////////////////////////////////////////////////

class LCVersionCheckOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new LCVersionCheckOK(); }

	// get packet name
	string getPacketName() const  { return "LCVersionCheckOK"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_LC_VERSION_CHECK_OK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCVersionCheckOKHandler;
//
//////////////////////////////////////////////////////////////////////

class LCVersionCheckOKHandler {
public:
    LCVersionCheckOKHandler () {};
    virtual ~LCVersionCheckOKHandler() {};
	// execute packet's handler
	static void execute(LCVersionCheckOK* pPacket, Player* pPlayer) ;

};

#endif
