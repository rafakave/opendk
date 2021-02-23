//////////////////////////////////////////////////////////////////////
// 
// Filename    : PacketFactoryManager.h 
// Written By  : reiot@ewestsoft.com
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __PACKET_FACTORY_MANAGER_H__
#define __PACKET_FACTORY_MANAGER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class PacketFactoryManager
//
//////////////////////////////////////////////////////////////////////

class PacketFactoryManager {

public :
	
	// constructor
	PacketFactoryManager () throw ();
	
	// destructor
	~PacketFactoryManager () throw ();

	// ��Ŷ���丮�Ŵ����� �ʱ�ȭ�Ѵ�.
	// ���Ӽ�����ü�� init()���� ȣ��ȴ�.
	void init () throw (Error);
	
	// ���丮 ��ü�� Ư�� �ε����� �߰��Ѵ�.
	void addFactory (PacketFactory* pFactory) throw (Error);
	
	// ��Ŷ���̵�� ��Ŷ��ü�� �����Ѵ�.
	Packet* createPacket (PacketID_t packetID) throw (InvalidProtocolException, Error);

	// Ư�� ��Ŷ�� �ִ� ũ�⸦ �����Ѵ�.
	string getPacketName (PacketID_t packetID) throw (InvalidProtocolException, Error);

	// Ư�� ��Ŷ�� �ִ� ũ�⸦ �����Ѵ�.
	PacketSize_t getPacketMaxSize (PacketID_t packetID) throw (InvalidProtocolException, Error);

	// get debug string
	string toString () const throw ();

private :
	
	// ��Ŷ���丮�� �迭
	PacketFactory ** m_Factories;
	
	// ��Ŷ���丮�迭�� ũ��
	ushort m_Size;

};

extern PacketFactoryManager* g_pPacketFactoryManager;

#endif