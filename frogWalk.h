#pragma once
#include "frogState.h"
class frogWalk : public frogState
{
private:
	animation* frogwalkright;
	animation* frogwalkleft;
public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

