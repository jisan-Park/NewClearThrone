#pragma once
#include "greenFrogState.h"
class greenFrogWalk : public greenFrogState
{
private:
	animation* greenfrogwalkright;
	animation* greenfrogwalkleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

