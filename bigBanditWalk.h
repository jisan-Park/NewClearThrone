#pragma once
#include "bigBanditState.h"
class bigBanditWalk :
	public bigBanditState
{

private:
	animation* bigbanditwalkright;
	animation* bigbanditwalkleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

