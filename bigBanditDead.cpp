#include "stdafx.h"
#include "bigBanditDead.h"

HRESULT bigBanditDead::init(enemyinfo info)
{
	bigbanditdeadright = new animation;
	bigbanditdeadright->init("bigbandit_dead");
	bigbanditdeadright->setPlayFrame(0, 9, false, false);
	bigbanditdeadright->setFPS(10);

	bigbanditdeadleft = new animation;
	bigbanditdeadleft->init("bigbandit_dead");
	bigbanditdeadleft->setPlayFrame(18, 9, false, false);
	bigbanditdeadleft->setFPS(10);



	_pt = info.pt;
	_img = IMAGEMANAGER->findImage("bigbandit_dead");
	if (info.direction == E_LEFT) _motion = bigbanditdeadleft;
	if (info.direction == E_RIGHT) _motion = bigbanditdeadright;
	_motion->start();
	return S_OK;
}

void bigBanditDead::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
