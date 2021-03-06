//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCThrowItemOK3.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_THROW_ITEM_OK_3_H__
#define __GC_THROW_ITEM_OK_3_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK3;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK3 : public Packet {

public :
	
	// constructor
	GCThrowItemOK3() ;
	
	// destructor
	~GCThrowItemOK3() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_THROW_ITEM_OK_3; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const  { return szObjectID + szObjectID; }

	// get packet's name
	string getPacketName() const  { return "GCThrowItemOK3"; }
	
	// get packet's debug string
	string toString() const ;

	// get / set ObjectID
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set TargetObjectID
	ObjectID_t getTargetObjectID() const  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t TargetObjectID)  { m_TargetObjectID = TargetObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK3Factory;
//
// Factory for GCThrowItemOK3
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK3Factory : public PacketFactory {

public :
	
	// constructor
	GCThrowItemOK3Factory()  {}
	
	// destructor
	virtual ~GCThrowItemOK3Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCThrowItemOK3(); }

	// get packet name
	string getPacketName() const  { return "GCThrowItemOK3"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_THROW_ITEM_OK_3; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK3Handler;
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK3Handler {

public :

	// execute packet's handler
	static void execute(GCThrowItemOK3* pGCThrowItemOK3, Player* pPlayer) ;

};

#endif
