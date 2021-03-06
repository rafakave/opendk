//////////////////////////////////////////////////////////////////////
// 
// Filename    : GuildMemberInfo2.h 
// Written By  : 
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GUILD_MEMBER_INFO2_H__
#define __GUILD_MEMBER_INFO2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class GuildMemberInfo2;
//
// 클라이언트에 길드 리스트를 보낸다.
//
//////////////////////////////////////////////////////////////////////

class GuildMemberInfo2 {

public :
	
	// constructor
	GuildMemberInfo2 () ;
	
	// destructor
	~GuildMemberInfo2 () ;

public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read (SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write (SocketOutputStream & oStream) const ;

	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getSize () ;

	static uint getMaxSize()  {
		return szGuildID + szBYTE + 20 + szGuildMemberRank + szbool;
	}

	// get packet's debug string
	string toString () const ;

	// get/set guild ID
	GuildID_t getGuildID() const  { return m_GuildID; }
	void setGuildID( GuildID_t guildID )  { m_GuildID = guildID; }

	// get/set Name
	string getName() const  { return m_Name; }
	void setName( const string& Name )  { m_Name = Name; }

	// get/set GuildMemberRank
	GuildMemberRank_t getRank() const  { return m_Rank; }
	void setRank( GuildMemberRank_t rank )  { m_Rank = rank; }

	// get/set logon
	bool getLogOn() const { return m_bLogOn; }
	void setLogOn( bool logOn ) { m_bLogOn = logOn; }

private :

	// 길드 아이디
	GuildID_t m_GuildID;

	// 이름
	string m_Name;

	// Guild Member Rank
	GuildMemberRank_t m_Rank;

	// log on
	bool m_bLogOn;

};

#endif
