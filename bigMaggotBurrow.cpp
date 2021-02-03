#include "stdafx.h"
#include "bigMaggotBurrow.h"

HRESULT bigMaggotBurrow::init(enemyinfo info)
{

	bigmaggotburrowright = new animation;
	bigmaggotburrowright->init("bigmaggot_burrow");
	bigmaggotburrowright->setPlayFrame(0, 11, false, false);
	bigmaggotburrowright->setFPS(10);

	bigmaggotburrowleft = new animation;
	bigmaggotburrowleft->init("bigmaggot_burrow");
	bigmaggotburrowleft->setPlayFrame(23, 12, false, false);
	bigmaggotburrowleft->setFPS(10);
	//
	bigmaggotappearright = new animation;
	bigmaggotappearright->init("bigmaggot_appear");
	bigmaggotappearright->setPlayFrame(0, 6, false, false);
	bigmaggotappearright->setFPS(10);

	bigmaggotappearleft = new animation;
	bigmaggotappearleft->init("bigmaggot_appear");
	bigmaggotappearleft->setPlayFrame(13, 7, false, false);
	bigmaggotappearleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("bigmaggot_burrow");
	if (info.direction == E_LEFT) _motion = bigmaggotburrowleft;
	if (info.direction == E_RIGHT) _motion = bigmaggotburrowright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void bigMaggotBurrow::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
