#pragma once
#include "scolpionState.h"
class scolpionIdle :
	public scolpionState
{
	animation* scolpionidleright;
	animation* scolpionidleleft;

public:

	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

