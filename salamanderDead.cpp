#include "stdafx.h"
#include "salamanderDead.h"

HRESULT salamanderDead::init(enemyinfo info)
{
	salamanderdeadright = new animation;
	salamanderdeadright->init("salamander_dead");
	salamanderdeadright->setPlayFrame(0, 8, false, false);
	salamanderdeadright->setFPS(10);

	salamanderdeadleft = new animation;
	salamanderdeadleft->init("salamander_dead");
	salamanderdeadleft->setPlayFrame(16, 8, false, false);
	salamanderdeadleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("salamander_dead");
	if (info.direction == E_LEFT) _motion = salamanderdeadleft;
	if (info.direction == E_RIGHT) _motion = salamanderdeadright;
	_motion->start();
	_pt = info.pt;

	return S_OK;
}

void salamanderDead::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
