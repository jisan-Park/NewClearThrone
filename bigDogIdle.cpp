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



	bigdogidlehurtright = new animation;
	bigdogidlehurtright->init("bigdog_idle_hurt");
	bigdogidlehurtright->setPlayFrame(0, 1, false, false, hurtFinish, this);
	bigdogidlehurtright->setFPS(10);

	bigdogidlehurtleft = new animation;
	bigdogidlehurtleft->init("bigdog_idle_hurt");
	bigdogidlehurtleft->setPlayFrame(3, 2, false, false, hurtFinish, this);
	bigdogidlehurtleft->setFPS(10);
	if (info.nstate == NOTICED)
	{
		_img = IMAGEMANAGER->findImage("bigdog_idle");
		if (info.direction == E_LEFT) _motion = bigdogidleright;
		if (info.direction == E_RIGHT) _motion = bigdogidleleft;

	}
	if (info.nstate == UNNOTICED)
	{
		_img = IMAGEMANAGER->findImage("bigdog_sleep");
		if (info.direction == E_LEFT) _motion = bigdogsleepright;
		if (info.direction == E_RIGHT) _motion = bigdogsleepleft;
	}
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void bigDogIdle::update(enemyinfo & info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("bigdog_idle_hurt");
		if (info.direction == E_LEFT) _motion = bigdogidlehurtleft;
		if (info.direction == E_RIGHT) _motion = bigdogidlehurtright;
	}
	else
	{
		if (info.nstate == NOTICED)
		{
			_img = IMAGEMANAGER->findImage("bigdog_idle");
			if (info.direction == E_LEFT) _motion = bigdogidleright;
			if (info.direction == E_RIGHT) _motion = bigdogidleleft;

		}
		if (info.nstate == UNNOTICED)
		{
			_img = IMAGEMANAGER->findImage("bigdog_sleep");
			if (info.direction == E_LEFT) _motion = bigdogsleepright;
			if (info.direction == E_RIGHT) _motion = bigdogsleepleft;
		}
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
