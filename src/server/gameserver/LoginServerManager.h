//////////////////////////////////////////////////////////////////////////////
// Filename    : LoginServerManager.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __LOGIN_SERVER_MANANGER_H__
#define __LOGIN_SERVER_MANANGER_H__

#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "DatagramSocket.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class LoginServerManager;
//
// 로그인 서버와의 통신을 전담하는 쓰레드이다.
// 내부에 데이터그램 서버소켓을 하나 가지고 블로킹 기반으로 동작한다.
//////////////////////////////////////////////////////////////////////////////

class LoginServerManager : public Thread 
{
public:
	LoginServerManager() ;
	~LoginServerManager() ;

public:
	void init()  {}

	void stop() ;

	void run() ;

	void sendDatagram(Datagram* pDatagram) ;

	void sendPacket(const string& host, uint port, DatagramPacket* pPacket) ;

	void lock() const  { m_Mutex.lock(); }
	void unlock() const  { m_Mutex.unlock(); }

private:
	DatagramSocket* m_pDatagramSocket; // UDP 서버 소켓

	mutable Mutex 	m_Mutex;
};

// global variable declaration
extern LoginServerManager* g_pLoginServerManager;

#endif
