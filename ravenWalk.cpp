#include "stdafx.h"
#include "ravenWalk.h"

HRESULT ravenWalk::init(enemyinfo info)
{
	ravenwalkright = new animation;
	ravenwalkright->init("raven_walk");
	ravenwalkright->setPlayFrame(0, 5, false, true);
	ravenwalkright->setFPS(10);

	ravenwalkleft = new animation;
	ravenwalkleft->init("raven_walk");
	ravenwalkleft->setPlayFrame(11, 6, false, true);
	ravenwalkleft->setFPS(10);

	ravenhurtright = new animation;
	ravenhurtright->init("raven_hurt");
	ravenhurtright->setPlayFrame(0, 2, false, false);
	ravenhurtright->setFPS(10);

	ravenhurtleft = new animation;
	ravenhurtleft->init("raven_hurt");
	ravenhurtleft->setPlayFrame(5, 3, false, false);
	ravenhurtleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("raven_walk");
	if (info.direction == E_LEFT) _motion = ravenwalkleft;
	if (info.direction == E_RIGHT) _motion = ravenwalkright;
	_motion->start();
	_pt = info.pt;

	return S_OK;
}

void ravenWalk::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
