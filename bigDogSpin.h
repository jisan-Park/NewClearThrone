#pragma once
#include "bigDogState.h"
class bigDogSpin :
	public bigDogState
{
private:

	bool _spinend;

	int _spincnt;
	float _dogangle;
	animation* bigdogspinendright;

	animation* bigdogspinendleft;
	animation* bigdogspin;

public:

	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
	void setSpinend(bool what) { _spinend = what; }

	static void spinend(void *obj);
};

