//----------------------------------------------------------------------
// 
// Filename    : GCMorphVampire2.h 
// Written By  : crazydog
// 
//----------------------------------------------------------------------

#ifndef __GC_MORPH_VAMPIRE2_H__
#define __GC_MORPH_VAMPIRE2_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCSlayerInfo3.h"
#include "PCVampireInfo3.h"


//----------------------------------------------------------------------
//
// class GCMorphVampire2;
//
// slayer등이 vampire로 변신하는 걸 지켜보는 분들에게 보낸다.
//----------------------------------------------------------------------

class GCMorphVampire2 : public Packet {

public :

	// constructor
	GCMorphVampire2()  {}
	GCMorphVampire2(PCVampireInfo3 info)  : m_VampireInfo3(info) {}
    ~GCMorphVampire2() {};
	
public :

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_MORPH_VAMPIRE_2; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return m_VampireInfo3.getSize(); }

	// get packet's name
	string getPacketName() const  { return "GCMorphVampire2"; }
	
	// get packet's debug string
	string toString() const ;


public :

	// get/set vampire info
	const PCVampireInfo3& getSlayerInfo()  { return m_VampireInfo3; }
	void setVampireInfo(PCVampireInfo3 info)  { m_VampireInfo3 = info; }


private :
	
	// 외모 정보
	PCVampireInfo3 m_VampireInfo3;
	
};


//--------------------------------------------------------------------------------
//
// class GCMorphVampire2Factory;
//
// Factory for GCMorphVampire2
//
//--------------------------------------------------------------------------------

class GCMorphVampire2Factory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCMorphVampire2(); }

	// get packet name
	string getPacketName() const  { return "GCMorphVampire2"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_MORPH_VAMPIRE_2; }

	// get packet's body size
	PacketSize_t getPacketMaxSize() const 
	{ 
		return PCVampireInfo3::getMaxSize();
	}

};


//--------------------------------------------------------------------------------
//
// class GCMorphVampire2Handler;
//
//--------------------------------------------------------------------------------

class GCMorphVampire2Handler {

public :

	// execute packet's handler
	static void execute(GCMorphVampire2* pPacket, Player* pPlayer) ;

};

#endif
