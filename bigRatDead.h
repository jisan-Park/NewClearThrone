#pragma once
#include "bigRatState.h"
class bigRatDead : public bigRatState
{
private:
	animation*	bigratdeadright;
	animation*	bigratdeadleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

