//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttackArmsOK1.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ATTACK_ARMS_OK_1_H__
#define __GC_ATTACK_ARMS_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"
//#include "ModifyItemInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK1;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK1 : public ModifyInfo {

public :
	
	// constructor
	GCAttackArmsOK1() ;
	
	// destructor
	~GCAttackArmsOK1() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_ATTACK_ARMS_OK_1; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const  { return szSkillType + szObjectID + szBullet + szbool + ModifyInfo::getPacketSize() ;}

	// get packet's name
	string getPacketName() const  { return "GCAttackArmsOK1"; }
	
	// get packet's debug string
	string toString() const ;

	SkillType_t getSkillType() const { return m_SkillType; }
	void setSkillType(SkillType_t skillType ) { m_SkillType = skillType; }
	// get / set Success
	bool getSkillSuccess() const  { return m_bSuccess; }
	void setSkillSuccess(bool Success)  { m_bSuccess = Success; }
	
	// get / set ObjectID
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set Bullet Num
	Bullet_t getBullet() const  { return m_BulletNum; }
	void setBulletNum(Bullet_t BulletNum) { m_BulletNum = BulletNum; }

private :

	SkillType_t m_SkillType;
	// ObjectID
	ObjectID_t m_ObjectID;

	// Bullet Num
	Bullet_t m_BulletNum;

	// success(damage 를 입혔나?)
	bool m_bSuccess;

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK1Factory;
//
// Factory for GCAttackArmsOK1
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCAttackArmsOK1Factory()  {}
	
	// destructor
	virtual ~GCAttackArmsOK1Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCAttackArmsOK1(); }

	// get packet name
	string getPacketName() const  { return "GCAttackArmsOK1"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ATTACK_ARMS_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szSkillType + szObjectID + szBullet + szbool + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK1Handler {

public :

	// execute packet's handler
	static void execute(GCAttackArmsOK1* pGCAttackArmsOK1, Player* pPlayer) ;

};

#endif
