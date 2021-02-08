#include "stdafx.h"
#include "greenMaggotDead.h"

HRESULT greenMaggotDead::init(enemyinfo info)
{
	greenmaggothurtright = new animation;
	greenmaggothurtright->init("greenmaggot_hurt");
	greenmaggothurtright->setPlayFrame(0, 2, false, false);
	greenmaggothurtright->setFPS(10);

	greenmaggothurtleft = new animation;
	greenmaggothurtleft->init("greenmaggot_hurt");
	greenmaggothurtleft->setPlayFrame(5, 3, false, false);
	greenmaggothurtleft->setFPS(10);

	greenmaggotdeadright = new animation;
	greenmaggotdeadright->init("greenmaggot_dead");
	greenmaggotdeadright->setPlayFrame(0, 6, false, false);
	greenmaggotdeadright->setFPS(10);

	greenmaggotdeadleft = new animation;
	greenmaggotdeadleft->init("greenmaggot_dead");
	greenmaggotdeadleft->setPlayFrame(12, 6, false, false);
	greenmaggotdeadleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("greenmaggot_dead");
	if (info.direction == E_LEFT) _motion = greenmaggotdeadleft;
	if (info.direction == E_RIGHT) _motion = greenmaggotdeadright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void greenMaggotDead::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
