//--------------------------------------------------------------------------------
//
// Filename   : TelephoneCenter.h
// Written By : elca
//
//--------------------------------------------------------------------------------

#ifndef __TELEPHONE_CENTER_H__
#define __TELEPHONE_CENTER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Slayer.h"
#include "Mutex.h"
#include <unordered_map>

//--------------------------------------------------------------------------------
// class TelephoneCenter;
//
// 게임 서버의 글로벌 매니저 객체로, PC의 폰번호를 사용해서 PC객체에 접근할 수 있도록
// 해준다. 내부적으로 unordered_map 을 사용해서, 검색 속도를 향상시킨다.
//
//--------------------------------------------------------------------------------
class TelephoneCenter {

public:

	// add creature to unordered_map
	// execute just once at PC's login
	void addSlayer(Slayer* pSlayer) ;

	// delete creature from unordered_map
	// execute just once at PC's logout
	void deleteSlayer(PhoneNumber_t PhoneNumber) ;

	// get creature with PC-name
	Slayer* getSlayer(PhoneNumber_t PhoneNumber) const ;

private:

	unordered_map< PhoneNumber_t, const Slayer* > m_PCs;

	mutable Mutex m_Mutex;
};

// global variable declaration
extern TelephoneCenter* g_pTelephoneCenter;

#endif
