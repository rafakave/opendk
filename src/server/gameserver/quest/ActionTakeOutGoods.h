//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTakeOutGoods.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TAKE_OUT_GOODS_H__
#define __ACTION_TAKE_OUT_GOODS_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTakeOutGoods
//////////////////////////////////////////////////////////////////////////////

class ActionTakeOutGoods : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_TAKE_OUT_GOODS; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:

private:
};


//////////////////////////////////////////////////////////////////////////////
// class ActionTakeOutGoodsFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTakeOutGoodsFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_TAKE_OUT_GOODS; }
	virtual string getActionName() const  { return "TakeOutGoods"; }
	virtual Action* createAction() const  { return new ActionTakeOutGoods(); }
};
#endif
