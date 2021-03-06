//////////////////////////////////////////////////////////////////////
// 
// Filename    : WorldInfo.h 
// Written By  : elca@ewestsoft.com
// Description : 인벤토리 아이템의 정보들
// 
//////////////////////////////////////////////////////////////////////

#ifndef __WORLD_INFO_H__
#define __WORLD_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class WorldInfo;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class WorldInfo {

public :
	
	// constructor
	WorldInfo () ;
	
	// destructor
	~WorldInfo () ;

public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read (SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write (SocketOutputStream & oStream) const ;

	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getSize () ;

	static uint getMaxSize()  {
		return (szBYTE + szBYTE + 20 + szBYTE)* 37;
	}

	// get packet's debug string
	string toString () const ;

	// get / set ID
	BYTE getID() const  { return m_ID; }
	void setID(WorldID_t ID)  { m_ID = ID; }

	// get / set Name
	string getName() const  { return m_Name; }
	void setName(string Name)  { m_Name = Name; }

	// get / set  Stat
	BYTE getStat() const  { return m_Stat; }
	void setStat(BYTE Stat)  { m_Stat = Stat; }

private :

	// 그룹 아이디
	WorldID_t m_ID;

	// 그룹 이름
	string m_Name;

	// 그룹의 상태
	BYTE	m_Stat;

};

#endif
