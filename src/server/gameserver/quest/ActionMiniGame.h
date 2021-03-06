//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionMiniGame.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_MINI_GAME_H__
#define __ACTION_MINI_GAME_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionMiniGame
//////////////////////////////////////////////////////////////////////////////

class ActionMiniGame : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_MINI_GAME; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
	int  getGameType() const  { return m_GameType; }
	void setGameType(int gameType)  { m_GameType = gameType; }

private:
	int m_GameType;   // 말할 대사 아이디
};


//////////////////////////////////////////////////////////////////////////////
// class ActionMiniGameFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionMiniGameFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_MINI_GAME; }
	virtual string getActionName() const  { return "MiniGame"; }
	virtual Action* createAction() const  { return new ActionMiniGame(); }
};
#endif
