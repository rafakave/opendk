//////////////////////////////////////////////////////////////////////////////
// Filename    : GCEnterVampirePortal.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCEnterVampirePortal.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GCEnterVampirePortal::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_X);
	iStream.read(m_Y);

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GCEnterVampirePortal::write (SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_ObjectID);
	oStream.write(m_X);
	oStream.write(m_Y);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GCEnterVampirePortal::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCEnterVampirePortalHandler::execute(this , pPlayer);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string GCEnterVampirePortal::toString() const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCEnterVampirePortal("
		<< "ObjectID:" << m_ObjectID 
		<< ",X:"       << (int)m_X
		<< ",Y:"        << (int)m_Y
		<< ")" ;
	return msg.toString();
		
	__END_CATCH
}
