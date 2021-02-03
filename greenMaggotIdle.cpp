#include "stdafx.h"
#include "greenMaggotIdle.h"

HRESULT greenMaggotIdle::init(enemyinfo info)
{//28,14
	greenmaggotidleright = new animation;
	greenmaggotidleright->init("greenmaggot_idle");
	greenmaggotidleright->setPlayFrame(0, 3, false, true);
	greenmaggotidleright->setFPS(10);

	greenmaggotidleleft = new animation;
	greenmaggotidleleft->init("greenmaggot_idle");
	greenmaggotidleleft->setPlayFrame(7, 4, false, true);
	greenmaggotidleleft->setFPS(10);
	_pt = info.pt;
	_img = IMAGEMANAGER->findImage("greenmaggot_idle");
	if (info.direction == E_LEFT) _motion = greenmaggotidleleft;
	if (info.direction == E_RIGHT) _motion = greenmaggotidleright;
	_motion->start();

	return S_OK;
}

void greenMaggotIdle::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
