//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLGetWorldList.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_GET_WORLD_LIST_H__
#define __CL_GET_WORLD_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLGetWorldList;
//
//////////////////////////////////////////////////////////////////////

class CLGetWorldList : public Packet {

public:
	CLGetWorldList() {};
    virtual ~CLGetWorldList() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CL_GET_WORLD_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return 0; }

	// get packet name
	string getPacketName() const  { return "CLGetWorldList"; }

	// get packet's debug string
	string toString() const  { return "CLGetWorldList"; }

private :

};


//////////////////////////////////////////////////////////////////////
//
// class CLGetWorldListFactory;
//
// Factory for CLGetWorldList
//
//////////////////////////////////////////////////////////////////////

class CLGetWorldListFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CLGetWorldList(); }

	// get packet name
	string getPacketName() const  { return "CLGetWorldList"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CL_GET_WORLD_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class CLGetWorldListHandler;
//
//////////////////////////////////////////////////////////////////////

class CLGetWorldListHandler {

public:

	// execute packet's handler
	static void execute(CLGetWorldList* pPacket, Player* player) ;

};

#endif
