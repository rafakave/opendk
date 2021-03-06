//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEventMeet.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_EVENT_MEET_H__
#define __ACTION_EVENT_MEET_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionEventMeet
//////////////////////////////////////////////////////////////////////////////

class ActionEventMeet : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_EVENT_MEET; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:

private:
	ScriptID_t m_ScriptID;   // 말할 대사 아이디
	ScriptID_t m_CounterScriptID;
	bool m_bGiveInfo;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionEventMeetFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionEventMeetFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_EVENT_MEET; }
	virtual string getActionName() const  { return "EventMeet"; }
	virtual Action* createAction() const  { return new ActionEventMeet(); }
};
#endif
