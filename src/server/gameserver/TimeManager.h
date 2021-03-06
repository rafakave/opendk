//////////////////////////////////////////////////////////////////////////////
// Filename   : TimeManager.h
// Written By : Reiot
//////////////////////////////////////////////////////////////////////////////

#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

#include "Types.h"
#include "GameTime.h"


#define DAWN_START_HOUR    4
#define DAWN_END_HOUR      8

#define DAY_START_HOUR     8
#define DAY_END_HOUR      16

#define DUSK_START_HOUR   16
#define DUSK_END_HOUR     20

#define NIGHT_START_HOUR  20
#define NIGHT_END_HOUR     4

enum Timeband
{
	TIME_DAWN = 0, // 새벽
	TIME_DAY,      // 낮
	TIME_DUSK,     // 저녁
	TIME_NIGHT,    // 밤

	TIME_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class TimeManager;
//
// 현재 게임 시간을 계산해주는 매니저 클래스이다.(사실 매니저라고 할 것도 없다.
// 이 외에도 뭔가 다른 역할을 할 것도 같다...
//////////////////////////////////////////////////////////////////////////////

class TimeManager 
{
public:
	void init() ;

	GameTime getGameTime() const ;	

	time_t getgametime() const ;

	time_t getBaseGameTime() const  { return m_BaseGameTime; }
	time_t getBaseRealTime() const  { return m_BaseRealTime; }

	bool isDawnTime(void) const ;
	bool isDayTime(void) const ;
	bool isDuskTime(void) const ;
	bool isNightTime(void) const ;
	uint getTimeband(void) const ;

	// get debug string
	string toString() const ;

private:
	time_t m_BaseGameTime;
	time_t m_BaseRealTime;
	
};

// global variable declaration
extern TimeManager* g_pTimeManager;

#endif
