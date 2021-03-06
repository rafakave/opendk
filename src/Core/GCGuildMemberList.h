//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGuildMemberList.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GUILD_MEMBER_LIST_H__
#define __GC_GUILD_MEMBER_LIST_H__

// include files
#include <list>
#include "Packet.h"
#include "PacketFactory.h"
#include "GuildMemberInfo.h"

typedef list<GuildMemberInfo*> GuildMemberInfoList;
typedef list<GuildMemberInfo*>::const_iterator GuildMemberInfoListConstItor;


//////////////////////////////////////////////////////////////////////
//
// class GCGuildMemberList;
//
// 클라이언트에 등록 대기중인 길드 리스트를 보낸다.
//
//////////////////////////////////////////////////////////////////////

class GCGuildMemberList : public Packet {

public :

	// constructor
	GCGuildMemberList() ;

	// destructor
	~GCGuildMemberList() ;
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_GUILD_MEMBER_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const ;

	// get packet name
	string getPacketName() const  { return "GCGuildMemberList"; }
	
	// get packet's debug string
	string toString() const ;

public:

	BYTE getListNum() const  { return m_GuildMemberInfoList.size(); }

	// add GuildMemberInfoList
	void addGuildMemberInfo(GuildMemberInfo* pGuildMemberInfo )  { m_GuildMemberInfoList.push_front(pGuildMemberInfo); }

	// clear GuildMemberInfoList
	void clearGuildMemberInfoList() ;

	// pop front Element in GuildMemberInfoList
	GuildMemberInfo* popFrontGuildMemberInfoList() 
	{
		if (!m_GuildMemberInfoList.empty() )
		{
			GuildMemberInfo* pGuildMemberInfo = m_GuildMemberInfoList.front();
			m_GuildMemberInfoList.pop_front();
			return pGuildMemberInfo;
		}
		return NULL;
	}

	BYTE getType() const { return m_Type; }
	void setType(BYTE type) { m_Type = type; }

private :
	BYTE m_Type;
	
	GuildMemberInfoList m_GuildMemberInfoList;	
};


//////////////////////////////////////////////////////////////////////
//
// class GCGuildMemberListFactory;
//
// Factory for GCGuildMemberList
//
//////////////////////////////////////////////////////////////////////

class GCGuildMemberListFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCGuildMemberList(); }

	// get packet name
	string getPacketName() const  { return "GCGuildMemberList"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_GUILD_MEMBER_LIST; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szBYTE + GuildMemberInfo::getMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCGuildMemberList;
//
//////////////////////////////////////////////////////////////////////

class GCGuildMemberListHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCGuildMemberList* pPacket, Player* pPlayer) ;

};

#endif
