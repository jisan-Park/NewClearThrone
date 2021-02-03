#pragma once
#include "assassinState.h"
class assassinIdle :
	public assassinState
{
private:
	animation* assassinfakeright;
	animation* assassinidleright;
	animation* assassinfakeleft;
	animation* assassinidleleft;

public:

	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

