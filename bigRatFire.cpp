#include "stdafx.h"
#include "bigRatFire.h"


HRESULT bigRatFire::init(enemyinfo info)
{
	bigratfireright = new animation;
	bigratfireright->init("bigrat_fire");
	bigratfireright->setPlayFrame(0, 1, false, false, isEndFire, this);
	bigratfireright->setFPS(10);


	bigratfireleft = new animation;
	bigratfireleft->init("bigrat_fire");
	bigratfireleft->setPlayFrame(3, 2, false, false, isEndFire, this);
	bigratfireleft->setFPS(10);

	bigrathurtright = new animation;
	bigrathurtright->init("bigrat_hurt");
	bigrathurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	bigrathurtright->setFPS(10);

	bigrathurtleft = new animation;
	bigrathurtleft->init("bigrat_hurt");
	bigrathurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	bigrathurtleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("bigrat_fire");
	if (info.direction == E_LEFT) _motion = bigratfireleft;
	if (info.direction == E_RIGHT)_motion = bigratfireright;
	_motion->start();
	_pt = info.pt;
	ENEMYMANAGER->createGreenRat(_pt);

	return S_OK;
}

void bigRatFire::isEndFire(void * obj)
{
	bigRatFire*m = (bigRatFire*)obj;
	m->isFireEnd = true;
}

void bigRatFire::update(enemyinfo & info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("bigrat_hurt");
		if (info.direction == E_LEFT) _motion = bigrathurtleft;
		if (info.direction == E_RIGHT)_motion = bigrathurtright;
	}
	else
	{
		if (isFireEnd == true) info.state = E_IDLE;
		_img = IMAGEMANAGER->findImage("bigrat_fire");

		if (PLAYERMANAGER->getPlayer()->getPt().x < info.pt.x)
		{
			info.direction == E_LEFT;
			_motion = bigratfireleft;
			_motion->start();
		}
		if (PLAYERMANAGER->getPlayer()->getPt().x > info.pt.x)
		{
			info.direction == E_RIGHT;
			_motion = bigratfireright;
			_motion->start();
		}

	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}


