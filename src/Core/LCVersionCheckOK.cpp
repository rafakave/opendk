//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCVersionCheckOK.cpp
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "LCVersionCheckOK.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
void LCVersionCheckOK::read (SocketInputStream & iStream )
	
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
void LCVersionCheckOK::write (SocketOutputStream & oStream ) const
	
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void LCVersionCheckOK::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	LCVersionCheckOKHandler::execute(this , pPlayer);
		
	__END_CATCH
}


