#include "stdafx.h"
#include "bigDogSpin.h"

HRESULT bigDogSpin::init(enemyinfo info)
{
	bigdogspin = new animation;
	bigdogspin->init("bigdog_spin");
	bigdogspin->setPlayFrame(0, 2, false, true);
	bigdogspin->setFPS(10);

	bigdogspinendright = new animation;
	bigdogspinendright->init("bigdog_spinend");
	bigdogspinendright->setPlayFrame(0, 1, false, false);
	bigdogspinendright->setFPS(10);

	bigdogspinendleft = new animation;
	bigdogspinendleft->init("bigdog_spinend");
	bigdogspinendleft->setPlayFrame(3, 1, false, false);
	bigdogspinendleft->setFPS(10);
	_img = IMAGEMANAGER->findImage("bigdog_spin");
	if (info.direction == E_LEFT) _motion = bigdogspin;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void bigDogSpin::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
