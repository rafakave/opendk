//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSetSlayerHotKey.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SET_SLAYER_HOT_KEY_H__
#define __CG_SET_SLAYER_HOT_KEY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGSetSlayerHotKey;
//
//////////////////////////////////////////////////////////////////////

class CGSetSlayerHotKey : public Packet {

public:
	CGSetSlayerHotKey() {};
    virtual ~CGSetSlayerHotKey() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_SET_SLAYER_HOT_KEY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGSetSlayerHotKeyPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const  { return szSkillType* 4; }

	// get packet name
	string getPacketName() const  { return "CGSetSlayerHotKey"; }
	
	// get packet's debug string
	string toString() const ;
	
public:

	// get/set X Coordicate
	SkillType_t getHotKey(BYTE pos) const  { return m_HotKey[pos]; }
	void setHotKey(BYTE pos, SkillType_t SkillType)  { m_HotKey[pos] = SkillType; }

private :

	SkillType_t m_HotKey[4];
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGSetSlayerHotKeyFactory;
//
// Factory for CGSetSlayerHotKey
//
//////////////////////////////////////////////////////////////////////

class CGSetSlayerHotKeyFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGSetSlayerHotKey(); }

	// get packet name
	string getPacketName() const  { return "CGSetSlayerHotKey"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_SET_SLAYER_HOT_KEY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGSetSlayerHotKeyPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szSkillType* 4; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGSetSlayerHotKeyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSetSlayerHotKeyHandler {
	
public:

	// execute packet's handler
	static void execute(CGSetSlayerHotKey* pPacket, Player* player) ;
};

#endif
