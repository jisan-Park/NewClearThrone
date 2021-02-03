#pragma once
#include "gatorState.h"
class gatorWalk : public gatorState
{
private:
	animation* gatorwalkright;
	animation* gatorwalkleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

