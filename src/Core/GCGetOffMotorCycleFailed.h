//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGetOffMotorCycleFailed.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GET_OFF_MOTORCYCLE_FAILED_H__
#define __GC_GET_OFF_MOTORCYCLE_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleFailed;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////
class GCGetOffMotorCycleFailed : public Packet {

public :
	
	// constructor
	GCGetOffMotorCycleFailed() ;
	
	// destructor
	~GCGetOffMotorCycleFailed() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_GET_OFF_MOTORCYCLE_FAILED; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const  { return 0; }

	// get packet's name
	string getPacketName() const  { return "GCGetOffMotorCycleFailed"; }
	
	// get packet's debug string
	string toString() const ;

private :
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleFailedFactory;
//
// Factory for GCGetOffMotorCycleFailed
//
//////////////////////////////////////////////////////////////////////
class GCGetOffMotorCycleFailedFactory : public PacketFactory {

public :
	
	// constructor
	GCGetOffMotorCycleFailedFactory()  {}
	
	// destructor
	virtual ~GCGetOffMotorCycleFailedFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCGetOffMotorCycleFailed(); }

	// get packet name
	string getPacketName() const  { return "GCGetOffMotorCycleFailed"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_GET_OFF_MOTORCYCLE_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleFailedHandler;
//
//////////////////////////////////////////////////////////////////////
class GCGetOffMotorCycleFailedHandler {

public :

	// execute packet's handler
	static void execute(GCGetOffMotorCycleFailed* pGCGetOffMotorCycleFailed, Player* pPlayer) ;

};

#endif
