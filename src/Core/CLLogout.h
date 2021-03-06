//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLLogout.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_LOGOUT_H__
#define __CL_LOGOUT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLLogout;
//
// 클라이언트가 서버에게 로그아웃을 알리는 패킷이다.
// data field 가 없기 때문에 getSize()는 0 을 리턴하며, read(), write() 
// 메쏘드는 아무런 역할도 하지 않는다.
//
//////////////////////////////////////////////////////////////////////

class CLLogout : public Packet {

public:
    CLLogout() {};
	virtual ~CLLogout() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CL_LOGOUT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return 0; }

	// get packet name
	string getPacketName() const  { return "CLLogout"; }
	
	// get packet's debug string
	string toString() const  { return "CLLogout"; }

};


//////////////////////////////////////////////////////////////////////
//
// class CLLogoutFactory;
//
// Factory for CLLogout
//
//////////////////////////////////////////////////////////////////////

class CLLogoutFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CLLogout(); }

	// get packet name
	string getPacketName() const  { return "CLLogout"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CL_LOGOUT; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class CLLogoutHandler;
//
//////////////////////////////////////////////////////////////////////

class CLLogoutHandler {

public:

	// execute packet's handler
	static void execute(CLLogout* pPacket, Player* player) ;

};

#endif
