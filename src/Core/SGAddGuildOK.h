//----------------------------------------------------------------------
// 
// Filename    : SGAddGuildOK.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __SG_ADD_GUILD_OK_H__
#define __SG_ADD_GUILD_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class SGAddGuildOK;
//
// 팀이 추가 되었음을 게임서버에 알린다.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class SGAddGuildOK : public Packet {

public:
	SGAddGuildOK() {};
    ~SGAddGuildOK() {};
    // Datagram 객체에서부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream& iStream) ;
		    
    // Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream& oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_SG_ADD_GUILD_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  
	{ 
		return szGuildID +				// guild ID
			   szBYTE +					// guild name length
			   m_GuildName.size() +		// guild name size
			   szGuildRace +			// guild race size
			   szGuildState +			// gulld state
			   szServerGroupID +		// server group ID
			   szZoneID +				// guild zone ID
			   szBYTE +					// guild master length
			   m_GuildMaster.size() +	// guild master
			   szBYTE +					// guild intro length
			   m_GuildIntro.size();		// guild intro
	}

	// get packet name
	string getPacketName() const  { return "SGAddGuildOK"; }
	
	// get packet's debug string
	string toString() const ;

public:

	// get/set guildID
	GuildID_t getGuildID() const  { return m_GuildID; }
	void setGuildID(GuildID_t guildID )  { m_GuildID = guildID; }

	// get/set guild name
	const string& getGuildName() const  { return m_GuildName; }
	void setGuildName(const string& name )  { m_GuildName = name; }

	// get/set guild race
	GuildRace_t getGuildRace() const  { return m_GuildRace; }
	void setGuildRace(GuildRace_t guildRace )  { m_GuildRace = guildRace; }

	// get/set guild state
	GuildState_t getGuildState() const  { return m_GuildState; }
	void setGuildState(GuildState_t guildState )  { m_GuildState = guildState; }

	// get/set server group ID
	ServerGroupID_t getServerGroupID() const  { return m_ServerGroupID; }
	void setServerGroupID(ServerGroupID_t serverGroupID )  { m_ServerGroupID = serverGroupID; }

	// get/set guild zone ID
	ZoneID_t getGuildZoneID() const  { return m_GuildZoneID; }
	void setGuildZoneID(ZoneID_t guildZoneID )  { m_GuildZoneID = guildZoneID; }

	// get/set guild master
	const string& getGuildMaster() const  { return m_GuildMaster; }
	void setGuildMaster(const string& master )  { m_GuildMaster = master; }

	// get/set guild intro
	const string& getGuildIntro() const  { return m_GuildIntro; }
	void setGuildIntro(const string& intro )  { m_GuildIntro = intro; }

private :

	// GuildID
	GuildID_t m_GuildID;

	// guild name
	string m_GuildName;

	// guild race
	GuildRace_t m_GuildRace;

	// guild state
	GuildState_t m_GuildState;

	// server group ID
	ServerGroupID_t m_ServerGroupID;

	// guild zone ID
	ZoneID_t m_GuildZoneID;

	// guild master
	string m_GuildMaster;

	// guild intro
	string m_GuildIntro;

};


//////////////////////////////////////////////////////////////////////
//
// class SGAddGuildOKFactory;
//
// Factory for SGAddGuildOK
//
//////////////////////////////////////////////////////////////////////

class SGAddGuildOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new SGAddGuildOK(); }

	// get packet name
	string getPacketName() const  { return "SGAddGuildOK"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_SG_ADD_GUILD_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  
	{ 
		return szGuildID +				// guild ID
			   szBYTE +					// guild name length
			   30 +						// guild name max size
			   szGuildRace +			// guild race size
			   szGuildState	+			// gulld state
			   szServerGroupID +		// server group ID
			   szZoneID +				// guild zone ID
			   szBYTE +					// guild master length
			   20 +						// guild master max size
			   szBYTE +					// guild intro length
			   256;						// guild intro max size
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class SGAddGuildOKHandler {
	
public:

	// execute packet's handler
	static void execute(SGAddGuildOK* pPacket) ;

};

#endif
