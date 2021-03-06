//--------------------------------------------------------------------------------
// 
// Filename    : CGNPCTalk.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __CG_NPC_TALK_H__
#define __CG_NPC_TALK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CGNPCTalk;
//
//--------------------------------------------------------------------------------

class CGNPCTalk : public Packet {

public:
	CGNPCTalk() {};
    ~CGNPCTalk() {};
	// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
	void read(SocketInputStream & iStream) ;
		    
	// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
	void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_NPC_TALK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGNPCTalkPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const  { return szObjectID; }

	// get packet name
	string getPacketName() const  { return "CGNPCTalk"; }
	
	// get packet's debug string
	string toString() const ;
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

};


//--------------------------------------------------------------------------------
//
// class CGNPCTalkFactory;
//
// Factory for CGNPCTalk
//
//--------------------------------------------------------------------------------

class CGNPCTalkFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGNPCTalk(); }

	// get packet name
	string getPacketName() const  { return "CGNPCTalk"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_NPC_TALK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGNPCTalkPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szObjectID; }

};


//--------------------------------------------------------------------------------
//
// class CGNPCTalkHandler;
//
//--------------------------------------------------------------------------------

class CGNPCTalkHandler {
	
public:

	// execute packet's handler
	static void execute(CGNPCTalk* pPacket, Player* player) ;
};

#endif
