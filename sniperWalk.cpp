#include "stdafx.h"
#include "sniperWalk.h"

HRESULT sniperWalk::init(enemyinfo info)
{
	sniperhurtright = new animation;
	sniperhurtright->init("sniper_hurt");
	sniperhurtright->setPlayFrame(0, 2, false, false);
	sniperhurtright->setFPS(10);

	sniperhurtleft = new animation;
	sniperhurtleft->init("sniper_hurt");
	sniperhurtleft->setPlayFrame(5, 3, false, false);
	sniperhurtleft->setFPS(10);
	sniperwalkright = new animation;
	sniperwalkright->init("sniper_walk");
	sniperwalkright->setPlayFrame(0, 5, false, true);
	sniperwalkright->setFPS(10);

	sniperwalkleft = new animation;
	sniperwalkleft->init("sniper_walk");
	sniperwalkleft->setPlayFrame(11, 6, false, true);
	sniperwalkleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("sniper_walk");
	if (info.direction == E_LEFT) _motion = sniperwalkleft;
	if (info.direction == E_RIGHT) _motion = sniperwalkright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void sniperWalk::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
