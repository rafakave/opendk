//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCBloodDrainOK1.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_BLOOD_DRAIN_OK_1_H__
#define __GC_BLOOD_DRAIN_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK1;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK1 : public ModifyInfo {

public :
	
	// constructor
	GCBloodDrainOK1() ;
	
	// destructor
	~GCBloodDrainOK1() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_BLOOD_DRAIN_OK_1; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const  { return szObjectID + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName() const  { return "GCBloodDrainOK1"; }
	
	// get packet's debug string
	string toString() const ;

	// get / set CEffectID
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;
};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK1Factory;
//
// Factory for GCBloodDrainOK1
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCBloodDrainOK1Factory()  {}
	
	// destructor
	virtual ~GCBloodDrainOK1Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCBloodDrainOK1(); }

	// get packet name
	string getPacketName() const  { return "GCBloodDrainOK1"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_BLOOD_DRAIN_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szObjectID + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK1Handler {

public :

	// execute packet's handler
	static void execute(GCBloodDrainOK1* pGCBloodDrainOK1, Player* pPlayer) ;

};

#endif
