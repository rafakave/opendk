//////////////////////////////////////////////////////////////////////////////
// Filename    : GCModifyInformation.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCModifyInformation.h"

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCModifyInformation::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCModifyInformationHandler::execute(this , pPlayer);
		
	__END_CATCH
}

