//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCHolyLandBonusInfo.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_HOLY_LAND_BONUS_INFO_H__
#define __GC_HOLY_LAND_BONUS_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "BloodBibleBonusInfo.h"
#include <list>

typedef list<BloodBibleBonusInfo*> BloodBibleBonusInfoList;
typedef BloodBibleBonusInfoList::const_iterator BloodBibleBonusInfoListConstItor;

//////////////////////////////////////////////////////////////////////
//
// class GCHolyLandBonusInfo;
//
//////////////////////////////////////////////////////////////////////

class GCHolyLandBonusInfo : public Packet {

public :

	// constructor
	GCHolyLandBonusInfo() ;

	// destructor
	~GCHolyLandBonusInfo() ;
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_HOLY_LAND_BONUS_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const ;

	// get packet name
	string getPacketName() const  { return "GCHolyLandBonusInfo"; }
	
	// get packet's debug string
	string toString() const ;

public:

	BYTE getListNum() const  { return m_BloodBibleBonusInfoList.size(); }

	void addBloodBibleBonusInfo(BloodBibleBonusInfo* pBloodBibleBonusInfo )  { m_BloodBibleBonusInfoList.push_back(pBloodBibleBonusInfo); }

	void clearBloodBibleBonusInfoList() ;

	BloodBibleBonusInfo* popFrontBloodBibleBonusInfoList() 
	{
		if (!m_BloodBibleBonusInfoList.empty() )
		{
			BloodBibleBonusInfo* pBloodBibleBonusInfo = m_BloodBibleBonusInfoList.front();
			m_BloodBibleBonusInfoList.pop_front();
			return pBloodBibleBonusInfo;
		}
		return NULL;
	}


private :
	
	BloodBibleBonusInfoList m_BloodBibleBonusInfoList;	
};


//////////////////////////////////////////////////////////////////////
//
// class GCHolyLandBonusInfoFactory;
//
// Factory for GCHolyLandBonusInfo
//
//////////////////////////////////////////////////////////////////////

class GCHolyLandBonusInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCHolyLandBonusInfo(); }

	// get packet name
	string getPacketName() const  { return "GCHolyLandBonusInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_HOLY_LAND_BONUS_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szBYTE + BloodBibleBonusInfo::getMaxSize() * 12 ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCHolyLandBonusInfo;
//
//////////////////////////////////////////////////////////////////////

class GCHolyLandBonusInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCHolyLandBonusInfo* pPacket, Player* pPlayer) ;

};

#endif
