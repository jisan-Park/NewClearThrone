#include "stdafx.h"
#include "greenFrogDead.h"

HRESULT greenFrogDead::init(enemyinfo info)
{
	greenfrogdeadright = new animation;
	greenfrogdeadright->init("greenfrog_dead");
	greenfrogdeadright->setPlayFrame(0, 7, false, false);
	greenfrogdeadright->setFPS(10);

	greenfrogdeadleft = new animation;
	greenfrogdeadleft->init("greenfrog_dead");
	greenfrogdeadleft->setPlayFrame(15, 8, false, false);
	greenfrogdeadleft->setFPS(10);

	_pt = info.pt;

	_img = IMAGEMANAGER->findImage("greenfrog_dead");
	if (info.direction == E_LEFT) _motion = greenfrogdeadleft;
	if (info.direction == E_RIGHT)_motion = greenfrogdeadright;

	_motion->start();
	return S_OK;
}

void greenFrogDead::update(enemyinfo & info)
{
	_pt = info.pt;

	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
