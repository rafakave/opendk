//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCDeletePCOK.cpp
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "LCDeletePCOK.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
void LCDeletePCOK::read (SocketInputStream & iStream )
	
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
void LCDeletePCOK::write (SocketOutputStream & oStream ) const
	
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void LCDeletePCOK::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	LCDeletePCOKHandler::execute(this , pPlayer);
		
	__END_CATCH
}


