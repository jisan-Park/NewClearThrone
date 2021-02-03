#include "stdafx.h"
#include "bigRatDead.h"


HRESULT bigRatDead::init(enemyinfo info)
{
	bigratdeadright = new animation;
	bigratdeadright->init("bigrat_dead");
	bigratdeadright->setPlayFrame(0, 5, false, false);
	bigratdeadright->setFPS(10);

	bigratdeadleft = new animation; // 콜백추가해야함
	bigratdeadleft->init("bigrat_dead");
	bigratdeadleft->setPlayFrame(10, 6, false, false);
	bigratdeadleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("bigrat_dead");
	if (info.direction == E_LEFT) _motion = bigratdeadleft;
	if (info.direction == E_RIGHT) _motion = bigratdeadright;
	_motion->start();
	_pt = info.pt;

	return S_OK;
}

void bigRatDead::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
