#include "stdafx.h"
#include "gatorDead.h"

HRESULT gatorDead::init(enemyinfo info)
{
	gatordeadright = new animation;
	gatordeadright->init("gator_dead");
	gatordeadright->setPlayFrame(0, 6, false, false);
	gatordeadright->setFPS(10);

	gatordeadleft = new animation;
	gatordeadleft->init("gator_dead");
	gatordeadleft->setPlayFrame(12, 6, false, false);
	gatordeadleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("gator_dead");
	if (info.direction == E_LEFT) _motion = gatordeadleft;
	if (info.direction == E_RIGHT)_motion = gatordeadright;
	_motion->start();
	_pt = info.pt;

	return S_OK;
}

void gatorDead::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

