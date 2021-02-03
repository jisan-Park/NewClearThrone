#pragma once
#include "assassinState.h"
class assassinDead :
	public assassinState
{
private:
	animation* assassindeadright;
	animation* assassindeadleft;

public:

	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);

};

