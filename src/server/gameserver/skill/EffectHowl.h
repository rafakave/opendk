//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHowl.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HOWL__
#define __EFFECT_HOWL__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHowl
//////////////////////////////////////////////////////////////////////////////

class EffectHowl : public Effect 
{
public:
	EffectHowl(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_HOWL; }

	void affect()  {}
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

	string toString() const throw();
};

#endif // __EFFECT_HOWL__
