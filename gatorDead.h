#pragma once
#include "gatorState.h"
class gatorDead : public gatorState
{
private:
	animation* gatordeadright;
	animation* gatordeadleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

