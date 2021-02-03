#pragma once
#include "greenRatState.h"
class greenRatDead : public greenRatState
{
private:
	animation* greenratdeadright;
	animation* greenratdeadleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

