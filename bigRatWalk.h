#pragma once
#include "bigRatState.h"
class bigRatWalk : public bigRatState
{
private:
	animation*	bigratwalkright;
	animation*	bigratwalkleft;


public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

