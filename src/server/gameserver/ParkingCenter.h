//////////////////////////////////////////////////////////////////////////////
// Filename    : ParkingCenter.h
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PARKING_CENTER_H__
#define __PARKING_CENTER_H__

#include "Types.h"
#include "Exception.h"
#include "Zone.h"
#include "item/Motorcycle.h"
#include "Mutex.h"
#include <unordered_map>
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class MotorcycleBox
//////////////////////////////////////////////////////////////////////////////

class MotorcycleBox 
{
public:
	MotorcycleBox(Motorcycle* pMotorcycle, Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) ;
	virtual ~MotorcycleBox() ;

public:
	Motorcycle* getMotorcycle()  { return m_pMotorcycle; }
	void setMotorcycle(Motorcycle* pMotorcycle)  { m_pMotorcycle = pMotorcycle; }

	Zone* getZone() const  { return m_pZone; }
	void setZone(Zone* pZone)  { m_pZone = pZone; }

	ZoneCoord_t getX() const  { return m_X; }
	void setX(ZoneCoord_t X)  { m_X = X; }

	ZoneCoord_t getY() const  { return m_Y; }
	void setY(ZoneCoord_t Y)  { m_Y = Y; }

	ItemID_t getItemID() const  { return m_pMotorcycle->getItemID(); }

	// 다른 zone으로 이동중인 오토바이
	bool isTransport() const  		{ return m_bTransport; }
	void setTransport(bool bTransport=true) { m_bTransport = bTransport; }

private:
	// 모토사이클 본체
	Motorcycle* m_pMotorcycle;

	// 현재 모토사이클이 있는 위치
	Zone* m_pZone;
	ZoneCoord_t m_X;
	ZoneCoord_t m_Y;

	// 다른 zone으로 이동 중. by sigi. 2002.5.23
	bool m_bTransport;
};

//////////////////////////////////////////////////////////////////////////////
// class ParkingCenter;
//////////////////////////////////////////////////////////////////////////////

class ParkingCenter 
{
public: 
	ParkingCenter() ;
	virtual ~ParkingCenter() ;
	
public:
	void addMotorcycleBox(MotorcycleBox* pMotorcycleBox) ;

	// 여기서 keyID는 열쇠의 TargetID를 뜻한다. 또한 Motorcycle의 ItemID이기도 하다.
	void deleteMotorcycleBox(ItemID_t keyTargetID) ;

	// 여기서 keyID는 열쇠의 TargetID를 뜻한다. 또한 Motorcycle의 ItemID이기도 하다.
	bool hasMotorcycleBox(ItemID_t keyTargetID) ;

	// 여기서 keyID는 열쇠의 TargetID를 뜻한다. 또한 Motorcycle의 ItemID이기도 하다.
	MotorcycleBox* getMotorcycleBox(ItemID_t keyTargetID) const ;

	// 주로 RemoveMotorcycles를 처리해준다. by sigi. 2003.2.26
	void	heartbeat() ;

private:
	// 여기서 ItemID_t는 오토바이의 ItemID를 말한다.
	unordered_map< ItemID_t, MotorcycleBox* > 	m_Motorcycles;
	list< MotorcycleBox* > 					m_RemoveMotorcycles;

	mutable Mutex m_Mutex;
	mutable Mutex m_MutexRemove;
};

// global variable declaration
extern ParkingCenter* g_pParkingCenter;

#endif
