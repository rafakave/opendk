//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCQueryResultCharacterName.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_QUERY_RESULT_CHARACTER_NAME_H__
#define __LC_QUERY_RESULT_CHARACTER_NAME_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultCharacterName;
//
// 클라이언트가 로그인 서버에게 최초에 전송하는 패킷이다.
// 아이디와 패스워드가 암호화되어 있다.
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultCharacterName : public Packet {

public:

	// constructor
	LCQueryResultCharacterName()  : m_bExist(false) {}
    ~LCQueryResultCharacterName() {};

public:

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_LC_QUERY_RESULT_CHARACTER_NAME; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  
	{ 
		return szbool
			+ szBYTE + m_CharacterName.size(); 
	}

	// get packet name
	string getPacketName() const  { return "LCQueryResultCharacterName"; }
	
	// get packet's debug string
	string toString() const ;

public:

	// get/set player id
	string getCharacterName() const  { return m_CharacterName; }
	void setCharacterName(const string & playerID)  { m_CharacterName = playerID; }

	// get/set player id's existence
	bool isExist() const  { return m_bExist; }
	void setExist(bool bExist = true)  { m_bExist = bExist; }

private :

	// player id
	string m_CharacterName;

	// player id's existence
	bool m_bExist;

};


//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultCharacterNameFactory;
//
// Factory for LCQueryResultCharacterName
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultCharacterNameFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new LCQueryResultCharacterName(); }

	// get packet name
	string getPacketName() const  { return "LCQueryResultCharacterName"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_LC_QUERY_RESULT_CHARACTER_NAME; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const 
	{ 
		return szbool
			+ szBYTE + 20; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultCharacterNameHandler;
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultCharacterNameHandler {

public:

	// execute packet's handler
	static void execute(LCQueryResultCharacterName* pPacket, Player* pPlayer) ;

};

#endif
