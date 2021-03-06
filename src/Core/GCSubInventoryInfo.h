//////////////////////////////////////////////////////////////////////////////
// Filename    : GCSubInventoryInfo.h 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SUB_INVENTORY_INFO_H__
#define __GC_SUB_INVENTORY_INFO_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "Types.h"

#include "InventoryInfo.h"

class GCSubInventoryInfo : public Packet
{
public:
	GCSubInventoryInfo() ;
	virtual ~GCSubInventoryInfo() ;

	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_SUB_INVENTORY_INFO; }
	PacketSize_t getPacketSize() const  { return szObjectID + m_pInventoryInfo->getSize(); }
	string getPacketName() const  { return "GCSubInventoryInfo"; }
	string toString() const ;

public:
	void		setObjectID(ObjectID_t ObjectID) { m_ObjectID = ObjectID; }
	ObjectID_t	getObjectID() const { return m_ObjectID; }

	void		setInventoryInfo(InventoryInfo* pInventoryInfo) { m_pInventoryInfo = pInventoryInfo; }
	InventoryInfo*	getInventoryInfo() const { return m_pInventoryInfo; }
private:
	ObjectID_t	m_ObjectID;
	InventoryInfo*	m_pInventoryInfo;
};

class GCSubInventoryInfoFactory : public PacketFactory {

public :
	
	Packet* createPacket()  { return new GCSubInventoryInfo(); }
	string getPacketName() const  { return "GCSubInventoryInfo"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SUB_INVENTORY_INFO; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + InventoryInfo::getMaxSize(); }
};

class GCSubInventoryInfoHandler {
	
public :
	static void execute(GCSubInventoryInfo* pPacket, Player* pPlayer) ;

};

#endif // __GC_SUB_INVENTORY_INFO_H__

