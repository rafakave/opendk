//////////////////////////////////////////////////////////////////////////////
// Filename    : EventKick.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_KICK_H__
#define __EVENT_KICK_H__

#include "Event.h"
#include "Zone.h"

//////////////////////////////////////////////////////////////////////////////
// class EventKick;
//////////////////////////////////////////////////////////////////////////////

class EventKick : public Event 
{
public:
	EventKick(GamePlayer* pGamePlayer) ;
	~EventKick() ;			

public:
	virtual EventClass getEventClass() const  { return EVENT_CLASS_KICK; }

	virtual void activate() ;
	void sendMessage() ;

	virtual string toString() const ;
};

#endif
