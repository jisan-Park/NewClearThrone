#pragma once
#include "maggotState.h"
class maggotDead :
	public maggotState
{
private:
	animation* maggothurtright;
	animation* maggotdeadright;
	animation* maggothurtleft;
	animation* maggotdeadleft;


public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

