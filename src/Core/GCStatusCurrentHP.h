//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCStatusCurrentHP.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_STATUS_CURRENT_HP_H__
#define __GC_STATUS_CURRENT_HP_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"


//////////////////////////////////////////////////////////////////////
//
// class GCStatusCurrentHP;
//
////////////////////////////////////////////////////////////////////

class GCStatusCurrentHP : public Packet {

public :

	GCStatusCurrentHP() ;

	virtual ~GCStatusCurrentHP() ;
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_STATUS_CURRENT_HP; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCStatusCurrentHPPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize() const  
	{ 
		return szObjectID + szHP; 
	}

	// get packet's name
	string getPacketName() const  { return "GCStatusCurrentHP"; }
	
	// get packet's debug string
	string toString() const ;

public :

	// get/set creature ID 
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	// get /set CurrentHP
	HP_t getCurrentHP() const  { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP)  { m_CurrentHP = CurrentHP; }

private :
	
    // 존 레벨에서 유니크한 아이디로 객체 구분을 위해서 사용한다.
    ObjectID_t m_ObjectID;

	// 몬스터 현재 체력
	HP_t m_CurrentHP;

};


//////////////////////////////////////////////////////////////////////
//
// class GCStatusCurrentHPFactory;
//
// Factory for GCStatusCurrentHP
//
//////////////////////////////////////////////////////////////////////

class GCStatusCurrentHPFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCStatusCurrentHP(); }

	// get packet name
	string getPacketName() const  { return "GCStatusCurrentHP"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_STATUS_CURRENT_HP; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCStatusCurrentHPPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  
	{ 
		return szObjectID + szHP; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCStatusCurrentHPHandler;
//
//////////////////////////////////////////////////////////////////////

class GCStatusCurrentHPHandler {

public :

	// execute packet's handler
	static void execute(GCStatusCurrentHP* pPacket, Player* pPlayer) ;

};

#endif
