//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToSelfOK3.h 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓴 기술이 성공했을때, 기술 시행자를 볼 수 없는 경우
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_SELF_OK_3_H__
#define __GC_SKILL_TO_SELF_OK_3_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToSelfOK3;
//
//
//////////////////////////////////////////////////////////////////////

class GCSkillToSelfOK3 : public Packet {

public :
	
	// constructor
	GCSkillToSelfOK3() ;
	
	// destructor
	~GCSkillToSelfOK3() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_SKILL_TO_SELF_OK_3; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const  { return szCoord*2 + szSkillType + szDuration + szBYTE; }

	// get packet's name
	string getPacketName() const  { return "GCSkillToSelfOK3"; }
	
	// get packet's debug string
	string toString() const ;

	// get / set X,Y
	Coord_t getX() const  { return m_X;}
	Coord_t getY() const  { return m_Y;}
	void setXY(Coord_t X, Coord_t Y)  { m_X = X; m_Y = Y;}


	// get / set SkillType
	SkillType_t getSkillType() const  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType)  { m_SkillType = SkillType; }

	// get / set Duration
	Duration_t getDuration() const  { return m_Duration; }
	void setDuration(Duration_t Duration)  { m_Duration = Duration; }

	BYTE getGrade() const  { return m_Grade; }
	void setGrade(BYTE grade )  { m_Grade = grade; }

private :
	
	// X,Y
	Coord_t m_X, m_Y;

	// SkillType
	SkillType_t m_SkillType;

	// Duration
	Duration_t m_Duration;

	BYTE m_Grade;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToSelfOK3Factory;
//
// Factory for GCSkillToSelfOK3
//
//////////////////////////////////////////////////////////////////////

class GCSkillToSelfOK3Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToSelfOK3Factory()  {}
	
	// destructor
	virtual ~GCSkillToSelfOK3Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCSkillToSelfOK3(); }

	// get packet name
	string getPacketName() const  { return "GCSkillToSelfOK3"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SKILL_TO_SELF_OK_3; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szCoord*2 + szSkillType + szDuration + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToSelfOK3Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToSelfOK3Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToSelfOK3* pGCSkillToSelfOK3, Player* pPlayer) ;

};

#endif
