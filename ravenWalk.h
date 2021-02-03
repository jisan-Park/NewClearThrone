#pragma once
#include "ravenState.h"
class ravenWalk :
	public ravenState
{
private:
	animation*	ravenhurtright;
	animation*	ravenwalkright;
	animation*	ravenhurtleft;
	animation*	ravenwalkleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

