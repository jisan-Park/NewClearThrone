#include "stdafx.h"
#include "ravenIdle.h"

HRESULT ravenIdle::init(enemyinfo info)
{
	ravenidleright = new animation;
	ravenidleright->init("raven_idle");
	ravenidleright->setPlayFrame(0, 8, false, true);
	ravenidleright->setFPS(10);

	ravenidleleft = new animation;
	ravenidleleft->init("raven_idle");
	ravenidleleft->setPlayFrame(15, 9, false, true);
	ravenidleleft->setFPS(10);

	ravenhurtright = new animation;
	ravenhurtright->init("raven_hurt");
	ravenhurtright->setPlayFrame(0, 2, false, false);
	ravenhurtright->setFPS(10);

	ravenhurtleft = new animation;
	ravenhurtleft->init("raven_hurt");
	ravenhurtleft->setPlayFrame(5, 3, false, false);
	ravenhurtleft->setFPS(10);


	_img = IMAGEMANAGER->findImage("raven_idle");
	if (info.direction == E_LEFT) _motion = ravenidleleft;
	if (info.direction == E_RIGHT) _motion = ravenidleright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void ravenIdle::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
