#include "stdafx.h"
#include "bigBanditFire.h"

HRESULT bigBanditFire::init(enemyinfo info)
{
	bigbanditfireright = new animation;
	bigbanditfireright->init("bigbandit_fire");
	bigbanditfireright->setPlayFrame(0, 8, false, false);
	bigbanditfireright->setFPS(10);

	bigbanditfireleft = new animation;
	bigbanditfireleft->init("bigbandit_fire");
	bigbanditfireleft->setPlayFrame(17, 9, false, false);
	bigbanditfireleft->setFPS(10);

	bigbandithurtright = new animation;
	bigbandithurtright->init("bigbandit_hurt");
	bigbandithurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	bigbandithurtright->setFPS(10);

	bigbandithurtleft = new animation;
	bigbandithurtleft->init("bigbandit_hurt");
	bigbandithurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	bigbandithurtleft->setFPS(10);

	_pt = info.pt;
	_img = IMAGEMANAGER->findImage("bigbandit_fire");
	if (info.direction == E_LEFT) _motion = bigbanditfireleft;
	if (info.direction == E_RIGHT) _motion = bigbanditfireright;
	_motion->start();
	return S_OK;
}

void bigBanditFire::update(enemyinfo & info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("bigbandit_hurt");
		if (info.direction == E_LEFT) _motion = bigbandithurtleft;
		if (info.direction == E_RIGHT) _motion = bigbandithurtright;
	}
	else
	{
		_img = IMAGEMANAGER->findImage("bigbandit_fire");
		if (info.direction == E_LEFT) _motion = bigbanditfireleft;
		if (info.direction == E_RIGHT) _motion = bigbanditfireright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
