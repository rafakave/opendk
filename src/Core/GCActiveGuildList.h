//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCActiveGuildList.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ACTIVE_GUILD_LIST_H__
#define __GC_ACTIVE_GUILD_LIST_H__

// include files
#include <list>
#include "Packet.h"
#include "PacketFactory.h"
#include "GuildInfo.h"

typedef list<GuildInfo*> GuildInfoList;
typedef list<GuildInfo*>::const_iterator GuildInfoListConstItor;


//////////////////////////////////////////////////////////////////////
//
// class GCActiveGuildList;
//
// 클라이언트에 등록 대기중인 길드 리스트를 보낸다.
//
//////////////////////////////////////////////////////////////////////

class GCActiveGuildList : public Packet {

public :

	// constructor
	GCActiveGuildList() ;

	// destructor
	~GCActiveGuildList() ;
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_ACTIVE_GUILD_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const ;

	// get packet name
	string getPacketName() const  { return "GCActiveGuildList"; }
	
	// get packet's debug string
	string toString() const ;

public:

	BYTE getListNum() const  { return m_GuildInfoList.size(); }

	// add GuildInfo
	void addGuildInfo(GuildInfo* pGuildInfo )  { m_GuildInfoList.push_front(pGuildInfo); }

	// clear GuildInfoList
	void clearGuildInfoList() ;

	// pop front Element in GuildInfoList
	GuildInfo* popFrontGuildInfoList() 
	{
		if (!m_GuildInfoList.empty() )
		{
			GuildInfo* pGuildInfo = m_GuildInfoList.front();
			m_GuildInfoList.pop_front();
			return pGuildInfo;
		}
		return NULL;
	}


private :
	
	GuildInfoList m_GuildInfoList;	
};


//////////////////////////////////////////////////////////////////////
//
// class GCActiveGuildListFactory;
//
// Factory for GCActiveGuildList
//
//////////////////////////////////////////////////////////////////////

class GCActiveGuildListFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCActiveGuildList(); }

	// get packet name
	string getPacketName() const  { return "GCActiveGuildList"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ACTIVE_GUILD_LIST; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szWORD + (GuildInfo::getMaxSize() * 5000); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCActiveGuildList;
//
//////////////////////////////////////////////////////////////////////

class GCActiveGuildListHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCActiveGuildList* pPacket, Player* pPlayer) ;

};

#endif
