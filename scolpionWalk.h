#pragma once
#include "scolpionState.h"
class scolpionWalk :
	public scolpionState
{
	animation* scolpionwalkright;
	animation* scolpionwalkleft;

public:

	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

