#include "stdafx.h"
#include "sniperDead.h"

HRESULT sniperDead::init(enemyinfo info)
{
	sniperdeadright = new animation;
	sniperdeadright->init("sniper_dead");
	sniperdeadright->setPlayFrame(0, 5, false, false);
	sniperdeadright->setFPS(10);

	sniperdeadleft = new animation;
	sniperdeadleft->init("sniper_dead");
	sniperdeadleft->setPlayFrame(11, 6, false, false);
	sniperdeadleft->setFPS(10);


	_img = IMAGEMANAGER->findImage("sniper_dead");
	if (info.direction == E_LEFT) _motion = sniperdeadleft;
	if (info.direction == E_RIGHT) _motion = sniperdeadright;
	_motion->start();
	_pt = info.pt;

	return S_OK;
}

void sniperDead::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
