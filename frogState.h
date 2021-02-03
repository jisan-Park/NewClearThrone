#pragma once
#include "enemyState.h"
class frogState :
	public enemyState
{
protected:
	animation* froghurtleft;
	animation* froghurtright;
public:
	virtual void setHurtAnimation();
};

