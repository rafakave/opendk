//////////////////////////////////////////////////////////////////////
//
// Filename    : GCThrowBombOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCThrowBombOK1.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCThrowBombOK1Handler::execute (GCThrowBombOK1 * pGCThrowBombOK1 , Player * pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __GAME_CLIENT__

	//cout << pGCThrowBombOK1->toString() << endl;
	
#elif __WINDOWS__
#endif

	__END_DEBUG_EX __END_CATCH
}
