#pragma once
#include "assassinState.h"
class assassinWalk :
	public assassinState
{
private:
	animation* assassinwalkright;
	animation* assassinwalkleft;
	animation* assassinhurtright;
	animation* assassinhurtleft;

public:

	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

