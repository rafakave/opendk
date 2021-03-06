//////////////////////////////////////////////////////////////////////////////
// Filename    : CGReloadFromQuickSlot.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGReloadFromQuickSlot.h"

CGReloadFromQuickSlot::CGReloadFromQuickSlot () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGReloadFromQuickSlot::~CGReloadFromQuickSlot () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGReloadFromQuickSlot::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_SlotID);

	__END_CATCH
}

void CGReloadFromQuickSlot::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_SlotID);

	__END_CATCH
}

void CGReloadFromQuickSlot::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGReloadFromQuickSlotHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGReloadFromQuickSlot::toString () 
	const 
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGReloadFromQuickSlot("
		<< "ObjectID : " << (int)m_ObjectID 
		<< ",SlotID: " << (int)m_SlotID 
		<< ")";
	return msg.toString();

	__END_CATCH
}
