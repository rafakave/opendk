//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionDenyReinforce.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_DENY_REINFORCE_H__
#define __ACTION_DENY_REINFORCE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionDenyReinforce
//////////////////////////////////////////////////////////////////////////////

class ActionDenyReinforce : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_DENY_REINFORCE; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2) ;
	virtual string toString() const ;

public:
	ZoneID_t	getZoneID() const { return m_ZoneID; }
	void		setZoneID( ZoneID_t ZoneID ) { m_ZoneID = ZoneID; }

private:
	ZoneID_t	m_ZoneID;	// 전쟁을 신청한 성의 ZoneID
};


//////////////////////////////////////////////////////////////////////////////
// class ActionDenyReinforceFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionDenyReinforceFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_DENY_REINFORCE; }
	virtual string getActionName() const  { return "DenyReinforce"; }
	virtual Action* createAction() const  { return new ActionDenyReinforce(); }
};
#endif
