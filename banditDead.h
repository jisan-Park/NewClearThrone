#pragma once
#include "banditState.h"
class banditDead :
	public banditState
{
private:
	animation* banditdeadright;
	animation* banditdeadleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

