#include "stdafx.h"
#include "ravenFly.h"

HRESULT ravenFly::init(enemyinfo info)
{
	ravenflyright = new animation;
	ravenflyright->init("raven_fly");
	ravenflyright->setPlayFrame(0, 4, false, true);
	ravenflyright->setFPS(10);

	ravenflyleft = new animation;
	ravenflyleft->init("raven_fly");
	ravenflyleft->setPlayFrame(9, 5, false, true);
	ravenflyleft->setFPS(10);

	ravenlandright = new animation;
	ravenlandright->init("raven_land");
	ravenlandright->setPlayFrame(0, 3, false, false);
	ravenlandright->setFPS(10);

	ravenlandleft = new animation;
	ravenlandleft->init("raven_land");
	ravenlandleft->setPlayFrame(7, 4, false, false);
	ravenlandleft->setFPS(10);



	ravenliftright = new animation;
	ravenliftright->init("raven_lift");
	ravenliftright->setPlayFrame(0, 4, false, false);
	ravenliftright->setFPS(10);

	ravenliftleft = new animation;
	ravenliftleft->init("raven_lift");
	ravenliftleft->setPlayFrame(9, 5, false, false);
	ravenliftleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("raven_lift");
	if (info.direction == E_LEFT) _motion = ravenliftleft;
	if (info.direction == E_RIGHT) _motion = ravenliftright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void ravenFly::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
