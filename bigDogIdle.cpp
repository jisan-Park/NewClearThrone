#include "stdafx.h"
#include "bigDogIdle.h"

HRESULT bigDogIdle::init(enemyinfo info)
{
	bigdogidleright = new animation;
	bigdogidleright->init("bigdog_idle");
	bigdogidleright->setPlayFrame(0, 5, false, true);
	bigdogidleright->setFPS(10);

	bigdogidleleft = new animation;
	bigdogidleleft->init("bigdog_idle");
	bigdogidleleft->setPlayFrame(11, 6, false, true);
	bigdogidleleft->setFPS(10);



	bigdogsleepright = new animation;
	bigdogsleepright->init("bigdog_sleep");
	bigdogsleepright->setPlayFrame(0, 13, false, true);
	bigdogsleepright->setFPS(10);

	bigdogsleepleft = new animation;
	bigdogsleepleft->init("bigdog_sleep");
	bigdogsleepleft->setPlayFrame(27, 14, false, true);
	bigdogsleepleft->setFPS(10);
	_img = IMAGEMANAGER->findImage("bigdog_sleep");
	if (info.direction == E_LEFT) _motion = bigdogsleepleft;
	if (info.direction == E_RIGHT) _motion = bigdogsleepright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void bigDogIdle::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
