#pragma once
#include "bigBanditState.h"
class bigBanditDead :
	public bigBanditState
{
private:
	animation* bigbanditdeadright;
	animation* bigbanditdeadleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

