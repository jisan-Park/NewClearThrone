#pragma once
#include "bigRatState.h"
class bigRatIdle :	public bigRatState
{
private:

	animation*	bigratidleright;
	animation*	bigratidleleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

