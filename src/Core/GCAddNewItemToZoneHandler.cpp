//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAddNewItemToZoneHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCAddNewItemToZone.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAddNewItemToZoneHandler::execute (GCAddNewItemToZone * pPacket , Player * pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__

	//cout << pPacket->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox(pPacket->toString().c_str());

#endif

	__END_DEBUG_EX __END_CATCH
}
