//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGuildMemberList.cpp 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCGuildMemberList.h"
#include <list>

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCGuildMemberList::GCGuildMemberList()
	
{
	m_Type=0;
}

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCGuildMemberList::~GCGuildMemberList()
	
{
	__BEGIN_TRY
	
	// 길드 리스트의 모든 객체를 삭제
	clearGuildMemberInfoList();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCGuildMemberList::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_Type);

	BYTE ListNum;

	iStream.read(ListNum);
	for (int i = 0; i < ListNum; i++ )
	{
		GuildMemberInfo* pGuildMemberInfo = new GuildMemberInfo();
		pGuildMemberInfo->read(iStream);
		m_GuildMemberInfoList.push_front(pGuildMemberInfo);
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCGuildMemberList::write (SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_Type);
	BYTE ListNum = m_GuildMemberInfoList.size();
	oStream.write(ListNum);

	GuildMemberInfoListConstItor itr = m_GuildMemberInfoList.begin();
	for (; itr != m_GuildMemberInfoList.end(); itr++ )
	{
		(*itr)->write(oStream);
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCGuildMemberList::clearGuildMemberInfoList()
	
{
	__BEGIN_TRY

	// GuildMemberInfoList 를 삭제한다
	while(!m_GuildMemberInfoList.empty() )
	{
		GuildMemberInfo* pGuildMemberInfo = m_GuildMemberInfoList.front();
		m_GuildMemberInfoList.pop_front();
		SAFE_DELETE(pGuildMemberInfo);
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCGuildMemberList::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCGuildMemberListHandler::execute(this , pPlayer);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet size
//////////////////////////////////////////////////////////////////////
PacketSize_t GCGuildMemberList::getPacketSize() const
	
{
	__BEGIN_TRY

	PacketSize_t PacketSize = szBYTE + szBYTE;

	GuildMemberInfoListConstItor itr = m_GuildMemberInfoList.begin();

	for (; itr != m_GuildMemberInfoList.end(); itr++ )
	{
		PacketSize += (*itr)->getSize();
	}

	return PacketSize;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCGuildMemberList::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCGuildMemberList(";

	list<GuildMemberInfo*>::const_iterator itr = m_GuildMemberInfoList.begin();
	for (; itr != m_GuildMemberInfoList.end(); itr++ )
	{
		msg << (*itr)->toString();
	}

	msg << ")";
	
	return msg.toString();
		
	__END_CATCH
}

