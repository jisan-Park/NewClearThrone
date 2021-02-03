#include "stdafx.h"
#include "greenRatDead.h"

HRESULT greenRatDead::init(enemyinfo info)
{

	greenratdeadright = new animation;
	greenratdeadright->init("greenrat_dead");
	greenratdeadright->setPlayFrame(0, 8, false, false);
	greenratdeadright->setFPS(10);

	greenratdeadleft = new animation;
	greenratdeadleft->init("greenrat_dead");
	greenratdeadleft->setPlayFrame(17, 9, false, false);
	greenratdeadleft->setFPS(10);


	_pt = info.pt;
	_img = IMAGEMANAGER->findImage("greenrat_dead");
	if (info.direction == E_LEFT) _motion = greenratdeadleft;
	if (info.direction == E_RIGHT)_motion = greenratdeadright;
	_motion->start();

	return S_OK;

}

void greenRatDead::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
