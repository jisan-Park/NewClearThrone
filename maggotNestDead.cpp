#include "stdafx.h"
#include "maggotNestDead.h"

HRESULT maggotNestDead::init(enemyinfo info)
{
	maggotnestdeadright = new animation;
	maggotnestdeadright->init("maggotnest_dead");
	maggotnestdeadright->setPlayFrame(0, 1, false, false);
	maggotnestdeadright->setFPS(10);

	maggotnestdeadleft = new animation;
	maggotnestdeadleft->init("maggotnest_dead");
	maggotnestdeadleft->setPlayFrame(3, 2, false, false);
	maggotnestdeadleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("maggotnest_dead");
	if (info.direction == E_LEFT) _motion = maggotnestdeadleft;
	if (info.direction == E_RIGHT) _motion = maggotnestdeadright;
	_motion->start();
	_pt = info.pt;

	return S_OK;
}

void maggotNestDead::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
