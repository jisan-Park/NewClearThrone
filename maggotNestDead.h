#pragma once
#include "maggotNestState.h"
class maggotNestDead :
	public maggotNestState
{
	animation* maggotnestdeadright;
	animation* maggotnestdeadleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
	void deadEffect();
};

