//////////////////////////////////////////////////////////////////////
// 
// Filename    : SGGuildMemberLogOnOK.cpp 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "SGGuildMemberLogOnOK.h"


//////////////////////////////////////////////////////////////////////
// Datagram 객체로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void SGGuildMemberLogOnOK::read (SocketInputStream& iStream ) 
{
	__BEGIN_TRY

	BYTE szName;

	iStream.read(m_GuildID);
	iStream.read(szName);

	if (szName == 0 )
		throw InvalidProtocolException("szName == 0");
	if (szName > 20 )
		throw InvalidProtocolException("too long name length");

	iStream.read(m_Name, szName);
	iStream.read(m_bLogOn);
	iStream.read(m_ServerID);
		
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void SGGuildMemberLogOnOK::write (SocketOutputStream& oStream ) const 
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();

	if (szName == 0 )
		throw InvalidProtocolException("szName == 0");
	if (szName > 20 )
		throw InvalidProtocolException("too long name length");

	oStream.write(m_GuildID);
	oStream.write(szName);
	oStream.write(m_Name);
	oStream.write(m_bLogOn);
	oStream.write(m_ServerID);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void SGGuildMemberLogOnOK::execute (Player * pPlayer ) 
{
#ifdef __GAME_SERVER__
  
	__BEGIN_TRY
		
	SGGuildMemberLogOnOKHandler::execute(this);
		
	__END_CATCH
#endif
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string SGGuildMemberLogOnOK::toString () const
{
	StringStream msg;

	msg << "SGGuildMemberLogOnOK("
		<< "GuildID:" << (int)m_GuildID
		<< "Name:" << m_Name
		<< "LogOn:" << m_bLogOn
		<< "ServerID:" << m_ServerID
		<< ")";

	return msg.toString();
}

