#pragma once
#include "bigDogState.h"
class bigDogIdle :
	public bigDogState
{
private:
	animation* bigdogidleleft;
	animation* bigdogidleright;
	animation* bigdogsleepleft;
	animation* bigdogsleepright;
public:

	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

