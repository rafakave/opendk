//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowMessageBox.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOW_MESSAGE_BOX_H__
#define __GC_SHOW_MESSAGE_BOX_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCShowMessageBox;
//
// 클라이언트에 길드 등록 창을 띄우도록 한다.
//
//////////////////////////////////////////////////////////////////////

class GCShowMessageBox : public Packet {

public :
	GCShowMessageBox() {};
    ~GCShowMessageBox() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_SHOW_MESSAGE_BOX; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName() const  { return "GCShowMessageBox"; }
	
	// get packet's debug string
	string toString() const ;

	// get/set Message
	string getMessage() const  { return m_Message; }
	void setMessage(const string& message )  { m_Message = message; }
	

private :
	
	// Message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCShowMessageBoxFactory;
//
// Factory for GCShowMessageBox
//
//////////////////////////////////////////////////////////////////////

class GCShowMessageBoxFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCShowMessageBox(); }

	// get packet name
	string getPacketName() const  { return "GCShowMessageBox"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SHOW_MESSAGE_BOX; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szBYTE + 256; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShowMessageBox;
//
//////////////////////////////////////////////////////////////////////

class GCShowMessageBoxHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCShowMessageBox* pPacket, Player* pPlayer) ;

};

#endif
