#include "stdafx.h"
#include "bigMaggotAppear.h"

HRESULT bigMaggotAppear::init(enemyinfo info)
{
	isBurrowEnd = false;
	bigmaggotappearright = new animation;
	bigmaggotappearright->init("bigmaggot_appear");
	bigmaggotappearright->setPlayFrame(0, 6, false, false, appearidle, this);
	bigmaggotappearright->setFPS(10);

	bigmaggotappearleft = new animation;
	bigmaggotappearleft->init("bigmaggot_appear");
	bigmaggotappearleft->setPlayFrame(13, 7, false, false, appearidle, this);
	bigmaggotappearleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("bigmaggot_appear");
	if (info.direction == E_LEFT) _motion = bigmaggotappearleft;
	if (info.direction == E_RIGHT) _motion = bigmaggotappearright;
	return S_OK;
}

void bigMaggotAppear::update(enemyinfo & info)
{
	_pt = info.pt;
	if (isBurrowEnd == true) info.nextState = E_IDLE;
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void bigMaggotAppear::appearidle(void * obj)
{
	bigMaggotAppear*m = (bigMaggotAppear*)obj;
	m->isBurrowEnd = true;
}
