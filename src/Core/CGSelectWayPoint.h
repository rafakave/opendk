//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectWayPoint.h 
// Written By  : excel96
// Description : 
// 슬레이어가 개인용 포탈을 이용해 다른 곳으로 이동하고자 할 때 보내는 패킷
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_WAYPOINT_H__
#define __CG_SELECT_WAYPOINT_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGSelectWayPoint;
//////////////////////////////////////////////////////////////////////////////

class CGSelectWayPoint : public Packet 
{
public:
    CGSelectWayPoint() {};
    virtual ~CGSelectWayPoint() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_SELECT_WAYPOINT; }
	PacketSize_t getPacketSize() const  { return szZoneID + szCoord*2; }
	string getPacketName() const  { return "CGSelectWayPoint"; }
	string toString() const ;

public:
	ZoneID_t getZoneID() const   { return m_ZoneID; }
	void setZoneID(ZoneID_t ZoneID)  { m_ZoneID = ZoneID; }

	Coord_t getX(void) const { return m_X; }
	void setX(Coord_t X) { m_X = X; }

	Coord_t getY(void) const { return m_Y; }
	void setY(Coord_t Y) { m_Y = Y; }

private:
	ZoneID_t   m_ZoneID;       // 가고자 하는 존의 ID
	Coord_t    m_X;            // 가고자 하는 존의 좌표 X
	Coord_t    m_Y;            // 가고자 하는 존의 좌표 Y

};

//////////////////////////////////////////////////////////////////////////////
// class CGSelectWayPointFactory;
//////////////////////////////////////////////////////////////////////////////

class CGSelectWayPointFactory : public PacketFactory 
{
	Packet* createPacket()  { return new CGSelectWayPoint(); }
	string getPacketName() const  { return "CGSelectWayPoint"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_SELECT_WAYPOINT; }
	PacketSize_t getPacketMaxSize() const  { return szZoneID + szCoord*2; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGSelectWayPointHandler;
//////////////////////////////////////////////////////////////////////////////

class CGSelectWayPointHandler 
{
public:
	static void execute(CGSelectWayPoint* pCGSelectWayPoint, Player* pPlayer) ;
	static void executeEnterQuestZone(CGSelectWayPoint* pCGSelectWayPoint, Player* pPlayer, int targetDynamicZoneType ) ;
};

#endif
