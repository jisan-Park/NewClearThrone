#pragma once
#include "bigDogState.h"
class bigDogSpin :
	public bigDogState
{
private:
	animation* bigdogspinendright;

	animation* bigdogspinendleft;
	animation* bigdogspin;

public:

	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

