#include "stdafx.h"
#include "maggotDead.h"

HRESULT maggotDead::init(enemyinfo info)
{
	maggothurtright = new animation;
	maggothurtright->init("maggot_hurt");
	maggothurtright->setPlayFrame(0, 2, false, false);
	maggothurtright->setFPS(10);

	maggothurtleft = new animation;
	maggothurtleft->init("maggot_hurt");
	maggothurtleft->setPlayFrame(5, 3, false, false);
	maggothurtleft->setFPS(10);

	maggotdeadright = new animation;
	maggotdeadright->init("maggot_dead");
	maggotdeadright->setPlayFrame(0, 5, false, false);
	maggotdeadright->setFPS(10);

	maggotdeadleft = new animation;
	maggotdeadleft->init("maggot_dead");
	maggotdeadleft->setPlayFrame(11, 6, false, false);
	maggotdeadleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("maggot_hurt");
	if (info.direction == E_LEFT) _motion = maggothurtleft;
	if (info.direction == E_RIGHT) _motion = maggothurtright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void maggotDead::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
