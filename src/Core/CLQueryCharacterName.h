//--------------------------------------------------------------------------------
// 
// Filename    : CLQueryCharacterName.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __CL_QUERY_CHARACTER_NAME_H__
#define __CL_QUERY_CHARACTER_NAME_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CLQueryCharacterName;
//
// 클라이언트가 로그인 서버에게 최초에 전송하는 패킷이다.
// 아이디와 패스워드가 암호화되어 있다.
//
//--------------------------------------------------------------------------------

class CLQueryCharacterName : public Packet {

public:
	CLQueryCharacterName() {};
    virtual ~CLQueryCharacterName() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CL_QUERY_CHARACTER_NAME; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  
	{ 
		return szBYTE + m_CharacterName.size(); 
	}

	// get packet name
	string getPacketName() const  { return "CLQueryCharacterName"; }
	
	// get packet's debug string
	string toString() const ;

public:

	// get/set player's id
	string getCharacterName() const  { return m_CharacterName; }
	void setCharacterName(const string & playerID)  { m_CharacterName = playerID; }

private :

	// 플레이어 아이디
	string m_CharacterName;

};


//--------------------------------------------------------------------------------
//
// class CLQueryCharacterNameFactory;
//
// Factory for CLQueryCharacterName
//
//--------------------------------------------------------------------------------

class CLQueryCharacterNameFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CLQueryCharacterName(); }

	// get packet name
	string getPacketName() const  { return "CLQueryCharacterName"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CL_QUERY_CHARACTER_NAME; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  
	{ 
		return szBYTE + 20; 
	}

};


//--------------------------------------------------------------------------------
//
// class CLQueryCharacterNameHandler;
//
//--------------------------------------------------------------------------------

class CLQueryCharacterNameHandler {

public:

	// execute packet's handler
	static void execute(CLQueryCharacterName* pPacket, Player* pPlayer) ;

};

#endif
