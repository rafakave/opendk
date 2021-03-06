//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCReloadOK.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RELOAD_OK_H__
#define __GC_RELOAD_OK_H__

// include files
#include "Packet.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCReloadOK;
//
//////////////////////////////////////////////////////////////////////

class GCReloadOK : public Packet {

public :

	// Constructor
	GCReloadOK() ;

	// Desctructor
	~GCReloadOK() ;
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_RELOAD_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCReloadOKPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const  { return szBullet; }

	// get packet name
	string getPacketName() const  { return "GCReloadOK"; }
	
	// get packet's debug string
	string toString() const ;

	// get / set BulletNum
	Bullet_t getBulletNum() const  { return m_BulletNum; }
	void setBulletNum(Bullet_t BulletNum)  { m_BulletNum = BulletNum; }
	

private :
	
	// BulletNum
	Bullet_t m_BulletNum;

};


//////////////////////////////////////////////////////////////////////
//
// class GCReloadOKFactory;
//
// Factory for GCReloadOK
//
//////////////////////////////////////////////////////////////////////

class GCReloadOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCReloadOK(); }

	// get packet name
	string getPacketName() const  { return "GCReloadOK"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_RELOAD_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCReloadOKPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szBullet; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCReloadOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCReloadOKHandler {
	
public :

	// execute packet's handler
	static void execute(GCReloadOK* pPacket, Player* player) ;
};

#endif
