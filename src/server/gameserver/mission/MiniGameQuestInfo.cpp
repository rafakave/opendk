#include "MiniGameQuestInfo.h"

MiniGameQuestStatus* MiniGameQuestInfo::makeQuestStatus( PlayerCreature *pPC ) const 
{
	__BEGIN_TRY

	return new MiniGameQuestStatus( getQuestID(), VSDateTime::currentDateTime().addSecs(getTimeLimit()), m_GameType );

	__END_CATCH
}

