//----------------------------------------------------------------------
// 
// Filename    : GSRequestGuildInfo.h 
// Written By  : 
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GS_REQUEST_GUILD_INFO_H__
#define __GS_REQUEST_GUILD_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GSRequestGuildInfo;
//
// 팀이 추가를 쉐어드 서버에 요청한다.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class GSRequestGuildInfo : public Packet {

public:
	GSRequestGuildInfo() {};
    ~GSRequestGuildInfo() {};
    // Stream 객체에서부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // Stream 객체로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GS_REQUEST_GUILD_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  
	{ 
		return 0;
	}

	// get packet name
	string getPacketName() const  { return "GSRequestGuildInfo"; }
	
	// get packet's debug string
	string toString() const  { return "GSRequestGuildInfo"; }
};


//////////////////////////////////////////////////////////////////////
//
// class GSRequestGuildInfoFactory;
//
// Factory for GSRequestGuildInfo
//
//////////////////////////////////////////////////////////////////////

class GSRequestGuildInfoFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new GSRequestGuildInfo(); }

	// get packet name
	string getPacketName() const  { return "GSRequestGuildInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GS_REQUEST_GUILD_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  
	{ 
		return 0;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class GSRequestGuildInfoHandler {
	
public:

	// execute packet's handler
	static void execute(GSRequestGuildInfo* pPacket, Player* pPlayer) ;

};

#endif
