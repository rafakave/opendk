#ifndef __MINI_GAME_QUEST_STATUS_H__
#define __MINI_GAME_QUEST_STATUS_H__

#include "QuestStatus.h"
#include "GCQuestStatus.h"

class MiniGameQuestStatus : public QuestStatus
{
public:
	MiniGameQuestStatus( QuestID_t qID, const VSDateTime& deadline, int gameType ) : QuestStatus( qID, deadline, QUEST_CLASS_MINI_GAME ), m_GameType(gameType)
	{
		m_bScoreSet = false;
		m_GameScore = 0;
	}
	virtual ~MiniGameQuestStatus() { }

	bool	isSuccess() const  { return m_bScoreSet; }

	int		getGameType() const { return m_GameType; }
	bool	setScore( uint score ) { if ( m_bScoreSet ) return false; m_GameScore = score; return m_bScoreSet = true; }
	GCQuestStatus*	makeStatusPacket() const;
	string	toStrong() const ;

	void	executeWhenStart();
	void	executeWhenFail();

private:
	int		m_GameType;
	uint	m_GameScore;
	bool	m_bScoreSet;
};

#endif // __MINI_GAME_QUEST_STATUS_H__
