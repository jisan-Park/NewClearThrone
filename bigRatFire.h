#pragma once
#include "bigRatState.h"
class bigRatFire :	public bigRatState
{
private:
	animation*	bigratfireright;
	animation*	bigratfireleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

