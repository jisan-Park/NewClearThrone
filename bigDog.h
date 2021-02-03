#pragma once
#include "enemy.h"
#include "bigDogIdle.h"
#include "bigDogSpin.h"
class bigDog :
	public enemy
{
private:
	animation* bigdogidleright;
	animation* bigdogsleepright;
	animation* bigdogspinendright;

	animation* bigdogidleleft;
	animation* bigdogsleepleft;
	animation* bigdogspinendleft;

	animation* bigdogspin;

public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
};

