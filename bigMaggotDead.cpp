#include "stdafx.h"
#include "bigMaggotDead.h"

HRESULT bigMaggotDead::init(enemyinfo info)
{
	bigmaggotdeadright = new animation;
	bigmaggotdeadright->init("bigmaggot_dead");
	bigmaggotdeadright->setPlayFrame(0, 6, false, false);
	bigmaggotdeadright->setFPS(10);

	bigmaggotdeadleft = new animation;
	bigmaggotdeadleft->init("bigmaggot_dead");
	bigmaggotdeadleft->setPlayFrame(7, 13, false, false);
	bigmaggotdeadleft->setFPS(10);
	_img = IMAGEMANAGER->findImage("bigmaggot_dead");
	if (info.direction == E_LEFT) _motion = bigmaggotdeadleft;
	if (info.direction == E_RIGHT) _motion = bigmaggotdeadright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void bigMaggotDead::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
