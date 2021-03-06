//----------------------------------------------------------------------
// 
// Filename    : GCMorphSlayer2.h 
// Written By  : crazydog
// 
//----------------------------------------------------------------------

#ifndef __GC_MORPH_SLAYER2_H__
#define __GC_MORPH_SLAYER2_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCSlayerInfo3.h"
#include "PCVampireInfo3.h"


//----------------------------------------------------------------------
//
// class GCMorphSlayer2;
//
// slayer등이 vampire로 변신하는 걸 지켜보는 분들에게 보낸다.
//----------------------------------------------------------------------

class GCMorphSlayer2 : public Packet {

public :

	// constructor
	GCMorphSlayer2()  {}
	GCMorphSlayer2(PCSlayerInfo3 info)  : m_SlayerInfo3(info) {}
    ~GCMorphSlayer2() {};
	
public :

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_MORPH_SLAYER_2; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return m_SlayerInfo3.getSize(); }

	// get packet's name
	string getPacketName() const  { return "GCMorphSlayer2"; }
	
	// get packet's debug string
	string toString() const ;


public :

	// get/set vampire info
	const PCSlayerInfo3& getSlayerInfo()  { return m_SlayerInfo3; }
	void setSlayerInfo(PCSlayerInfo3  info)  { m_SlayerInfo3 = info; }


private :
	
	// 외모 정보
	PCSlayerInfo3 m_SlayerInfo3;
	
};


//--------------------------------------------------------------------------------
//
// class GCMorphSlayer2Factory;
//
// Factory for GCMorphSlayer2
//
//--------------------------------------------------------------------------------

class GCMorphSlayer2Factory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCMorphSlayer2(); }

	// get packet name
	string getPacketName() const  { return "GCMorphSlayer2"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_MORPH_SLAYER_2; }

	// get packet's body size
	PacketSize_t getPacketMaxSize() const 
	{ 
		return PCSlayerInfo3::getMaxSize();
	}

};


//--------------------------------------------------------------------------------
//
// class GCMorphSlayer2Handler;
//
//--------------------------------------------------------------------------------

class GCMorphSlayer2Handler {

public :

	// execute packet's handler
	static void execute(GCMorphSlayer2* pPacket, Player* pPlayer) ;

};

#endif
