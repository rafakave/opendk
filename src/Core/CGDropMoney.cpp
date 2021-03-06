//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDropMoney.cpp 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGDropMoney.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert1.h"


CGDropMoney::CGDropMoney () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGDropMoney::~CGDropMoney () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGDropMoney::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		pEIStream->readEncrypt(m_Amount);
	}
	else
#endif
	{
		iStream.read(m_Amount);
	}

	__END_CATCH
}

void CGDropMoney::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		pEOStream->writeEncrypt(m_Amount);
	}
	else
#endif
	{
		oStream.write(m_Amount);
	}

	__END_CATCH
}

void CGDropMoney::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGDropMoneyHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGDropMoney::toString () 
	const 
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGDropMoney("
		<< "Amount:" << (int)m_Amount
		<< ")";
	return msg.toString();

	__END_CATCH
}
