//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGQuestStatusInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCGQuestStatusInfo.h"


//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCGQuestStatusInfo::GCGQuestStatusInfo () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCGQuestStatusInfo::~GCGQuestStatusInfo () 
    
{
	__BEGIN_TRY

/*	list<QuestStatusInfo*>::iterator itr = m_Infos.begin();

	for (; itr != m_Infos.end() ; ++itr )
	{
		SAFE_DELETE((*itr));
	}*/

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCGQuestStatusInfo::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY

	BYTE size;
	iStream.read(size);

	for (int i=0; i<size; ++i )
	{
		QuestStatusInfo* pInfo = new QuestStatusInfo(0);
		pInfo->read(iStream);
		m_Infos.push_back(pInfo);
	}

	
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCGQuestStatusInfo::write (SocketOutputStream & oStream ) 
     const 
{
	__BEGIN_TRY

	BYTE size = m_Infos.size();
	oStream.write(size);
	//cout << "퀘스트 개수 : " << (int)size << endl;

	list<QuestStatusInfo*>::const_iterator itr = m_Infos.begin();

	for (; itr != m_Infos.end(); ++itr )
	{
		(*itr)->write(oStream);
	}
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCGQuestStatusInfo::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCGQuestStatusInfoHandler::execute(this , pPlayer);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCGQuestStatusInfo::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCGQuestStatusInfo("
		<< ")";
	return msg.toString();

	__END_CATCH
}


