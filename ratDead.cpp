#include "stdafx.h"
#include "ratDead.h"

HRESULT ratDead::init(enemyinfo info)
{
	ratdeadright = new animation;
	ratdeadright->init("rat_dead");
	ratdeadright->setPlayFrame(0, 5, false, false);
	ratdeadright->setFPS(10);

	ratdeadleft = new animation;
	ratdeadleft->init("rat_dead");
	ratdeadleft->setPlayFrame(11, 6, false, false);
	ratdeadleft->setFPS(10);

	_pt = info.pt;
	_img = IMAGEMANAGER->findImage("rat_dead");
	if (info.direction == E_LEFT) _motion = ratdeadleft;
	if (info.direction == E_RIGHT)_motion = ratdeadright;
	_motion->start();
	

	return S_OK;
}

void ratDead::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
