//////////////////////////////////////////////////////////////////////////////
// Filename    : GCGQuestStatusInfo.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_GGQUEST_STATUS_INFO_H__
#define __GC_GGQUEST_STATUS_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "QuestStatusInfo.h"

#include <numeric>
#include <functional>

#define MAX_QUEST_NUM 100

//////////////////////////////////////////////////////////////////////////////
// class GCGQuestStatusInfo;
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//////////////////////////////////////////////////////////////////////////////

class GCGQuestStatusInfo : public Packet 
{
public:
	GCGQuestStatusInfo() ;
	~GCGQuestStatusInfo() ;
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_GQUEST_STATUS_INFO; }
	PacketSize_t getPacketSize() const  { return accumulate(m_Infos.begin(), m_Infos.end(), szBYTE, addSize); }
	string getPacketName() const  { return "GCGQuestStatusInfo"; }
	string toString() const ;

public:
	static PacketSize_t	addSize(PacketSize_t tot, const QuestStatusInfo* pInfo ) { return tot + pInfo->getSize(); }

	list<QuestStatusInfo*>&	getInfos() { return m_Infos; }
	const list<QuestStatusInfo*>&	getInfos() const { return m_Infos; }

private:
	list<QuestStatusInfo*>	m_Infos;
};


//////////////////////////////////////////////////////////////////////////////
// class GCGQuestStatusInfoFactory;
//////////////////////////////////////////////////////////////////////////////

class GCGQuestStatusInfoFactory : public PacketFactory 
{
public :
	GCGQuestStatusInfoFactory()  {}
	virtual ~GCGQuestStatusInfoFactory()  {}
	
public:
	Packet* createPacket()  { return new GCGQuestStatusInfo(); }
	string getPacketName() const  { return "GCGQuestStatusInfo"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_GQUEST_STATUS_INFO; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE + QuestStatusInfo::getMaxSize() * MAX_QUEST_NUM; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCGQuestStatusInfoHandler;
//////////////////////////////////////////////////////////////////////////////

class GCGQuestStatusInfoHandler 
{
public:
	static void execute(GCGQuestStatusInfo* pGCGQuestStatusInfo, Player* pPlayer) ;

};

#endif
