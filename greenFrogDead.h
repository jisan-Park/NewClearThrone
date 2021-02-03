#pragma once
#include "greenFrogState.h"
class greenFrogDead :public greenFrogState
{
private:
	animation* greenfrogdeadright;
	animation* greenfrogdeadleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

