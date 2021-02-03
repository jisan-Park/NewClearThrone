#include "stdafx.h"
#include "ravenDead.h"

HRESULT ravenDead::init(enemyinfo info)
{
	ravendeadright = new animation;
	ravendeadright->init("raven_dead");
	ravendeadright->setPlayFrame(0, 5, false, false);
	ravendeadright->setFPS(10);

	ravendeadleft = new animation;
	ravendeadleft->init("raven_dead");
	ravendeadleft->setPlayFrame(11, 6, false, false);
	ravendeadleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("raven_dead");
	if (info.direction == E_LEFT) _motion = ravendeadleft;
	if (info.direction == E_RIGHT) _motion = ravendeadright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void ravenDead::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
