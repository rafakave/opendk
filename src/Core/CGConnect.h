//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGConnect.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_CONNECT_H__
#define __CG_CONNECT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGConnect;
//
// 클라이언트가 서버에게 보내는 연결 패킷이다.
// 서버간 이동에 사용되며, 이전 서버가 준 Key 를 새 서버에게 전송해서
// 인증을 받는다. 또한, 새 서버에서 사용할 크리처 아이디를 담고 있다.
//
//////////////////////////////////////////////////////////////////////

class CGConnect : public Packet {

public:
	CGConnect() {};
    ~CGConnect() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_CONNECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  
	{ 
		return szDWORD 						// authentication key
			+ szPCType 						// Slayer or Vampire?
			+ szBYTE + m_PCName.size() + 6; 	// name
	}

	// get packet name
	string getPacketName() const  { return "CGConnect"; }
	
	// get packet's debug string
	string toString() const ;

public:

	// get/set key
	DWORD getKey() const  { return m_Key; }
	void setKey(DWORD key)  { m_Key = key; }

	// get/set PCType
	PCType getPCType() const  { return m_PCType; }
	void setPCType(PCType pcType)  { m_PCType = pcType; }
	
	// get/set pc name
	string getPCName() const  { return m_PCName; }
	void setPCName(string pcName)  { m_PCName = pcName; }

	const BYTE* getMacAddress() const { return m_MacAddress; }

private :
	
	// authentication key
	DWORD m_Key;

	// Slayer or Vampire?
	PCType m_PCType;

	// PC의 이름
	string m_PCName;
	
	BYTE m_MacAddress[6];
};


//////////////////////////////////////////////////////////////////////
//
// class CGConnectFactory;
//
// Factory for CGConnect
//
//////////////////////////////////////////////////////////////////////

class CGConnectFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGConnect(); }

	// get packet name
	string getPacketName() const  { return "CGConnect"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_CONNECT; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const 
	{ 
		return szDWORD 			// authentication key
			+ szPCType 			// Slayer or Vampire
			+ szBYTE + 20 + 6; 		// name
	}

};

//////////////////////////////////////////////////////////////////////
//
// class CGConnectHandler;
//
//////////////////////////////////////////////////////////////////////

class CGConnectHandler {

public:

	// execute packet's handler
	static void execute(CGConnect* pPacket, Player* pPlayer) ;

};

#endif
