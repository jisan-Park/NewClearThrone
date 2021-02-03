#include "stdafx.h"
#include "scolpionDead.h"

HRESULT scolpionDead::init(enemyinfo info)
{
	scolpiondeadright = new animation;
	scolpiondeadright->init("scolpion_dead");
	scolpiondeadright->setPlayFrame(0, 5, false, false);
	scolpiondeadright->setFPS(10);

	scolpiondeadleft = new animation;
	scolpiondeadleft->init("scolpion_dead");
	scolpiondeadleft->setPlayFrame(11, 6, false, false);
	scolpiondeadleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("scolpion_dead");
	if (info.direction == E_LEFT) _motion = scolpiondeadleft;
	if (info.direction == E_RIGHT) _motion = scolpiondeadright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void scolpionDead::update(enemyinfo & info)
{
	_pt = info.pt;
	
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
