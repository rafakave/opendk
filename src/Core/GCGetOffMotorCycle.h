//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGetOffMotorCycle.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GET_OFF_MOTORCYCLE_H__
#define __GC_GET_OFF_MOTORCYCLE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycle;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCGetOffMotorCycle : public Packet {

public :
	
	// constructor
	GCGetOffMotorCycle() ;
	
	// destructor
	~GCGetOffMotorCycle() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_GET_OFF_MOTORCYCLE; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const  { return szObjectID; }

	// get packet's name
	string getPacketName() const  { return "GCGetOffMotorCycle"; }
	
	// get packet's debug string
	string toString() const ;

	// get / set ObjectID
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleFactory;
//
// Factory for GCGetOffMotorCycle
//
//////////////////////////////////////////////////////////////////////

class GCGetOffMotorCycleFactory : public PacketFactory {

public :
	
	// constructor
	GCGetOffMotorCycleFactory()  {}
	
	// destructor
	virtual ~GCGetOffMotorCycleFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCGetOffMotorCycle(); }

	// get packet name
	string getPacketName() const  { return "GCGetOffMotorCycle"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_GET_OFF_MOTORCYCLE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleHandler;
//
//////////////////////////////////////////////////////////////////////

class GCGetOffMotorCycleHandler {

public :

	// execute packet's handler
	static void execute(GCGetOffMotorCycle* pGCGetOffMotorCycle, Player* pPlayer) ;

};

#endif
