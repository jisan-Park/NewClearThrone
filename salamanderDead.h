#pragma once
#include "salamanderState.h"
class salamanderDead :
	public salamanderState
{
private:
	animation* salamanderdeadright;
	animation* salamanderdeadleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

