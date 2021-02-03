#include "stdafx.h"
#include "assassinDead.h"

HRESULT assassinDead::init(enemyinfo info)
{
	assassindeadright = new animation;
	assassindeadright->init("assassin_dead");
	assassindeadright->setPlayFrame(0, 5, false, false);
	assassindeadright->setFPS(10);

	assassindeadleft = new animation;
	assassindeadleft->init("assassin_dead");
	assassindeadleft->setPlayFrame(11, 6, false, false);
	assassindeadleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("assassin_dead");
	if (info.direction == E_LEFT) _motion = assassindeadleft;
	if (info.direction == E_RIGHT) _motion = assassindeadright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void assassinDead::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
