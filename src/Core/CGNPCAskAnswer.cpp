//////////////////////////////////////////////////////////////////////////////
// Filename    : CGNPCAskAnswer.cpp 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGNPCAskAnswer.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert1.h"


void CGNPCAskAnswer::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_3(pEIStream->getEncryptCode(),
							pEIStream->readEncrypt(m_ObjectID),
							pEIStream->readEncrypt(m_ScriptID),
							pEIStream->readEncrypt(m_AnswerID));
	}
	else
#endif
	{
		iStream.read(m_ObjectID);
		iStream.read(m_ScriptID);
		iStream.read(m_AnswerID);
	}

	__END_CATCH
}

void CGNPCAskAnswer::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_3(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt(m_ObjectID),
							pEOStream->writeEncrypt(m_ScriptID),
							pEOStream->writeEncrypt(m_AnswerID));
	}
	else
#endif
	{
		oStream.write(m_ObjectID);
		oStream.write(m_ScriptID);
		oStream.write(m_AnswerID);
	}

	__END_CATCH
}

void CGNPCAskAnswer::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGNPCAskAnswerHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGNPCAskAnswer::toString () const 
	
{
	StringStream msg;
	msg << "CGNPCAskAnswer(" 
		<< "ObjectID : " << (int)m_ObjectID << ","
		<< (int)m_ScriptID << ","
		<< (int)m_AnswerID << ","
		<< ")";
	return msg.toString();
}
