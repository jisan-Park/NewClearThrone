#include "stdafx.h"
#include "bigBanditWalk.h"

HRESULT bigBanditWalk::init(enemyinfo info)
{
	bigbanditwalkright = new animation;
	bigbanditwalkright->init("bigbandit_walk");
	bigbanditwalkright->setPlayFrame(0, 7, false, true);
	bigbanditwalkright->setFPS(10);

	bigbanditwalkleft = new animation;
	bigbanditwalkleft->init("bigbandit_walk");
	bigbanditwalkleft->setPlayFrame(15, 8, false, true);
	bigbanditwalkleft->setFPS(10);

	bigbandithurtright = new animation;
	bigbandithurtright->init("bigbandit_hurt");
	bigbandithurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	bigbandithurtright->setFPS(10);

	bigbandithurtleft = new animation;
	bigbandithurtleft->init("bigbandit_hurt");
	bigbandithurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	bigbandithurtleft->setFPS(10);



	_pt = info.pt;
	_img = IMAGEMANAGER->findImage("bigbandit_walk");
	if (info.direction == E_LEFT) _motion = bigbanditwalkleft;
	if (info.direction == E_RIGHT) _motion = bigbanditwalkright;
	_motion->start();
	return S_OK;
}

void bigBanditWalk::update(enemyinfo & info)
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
		_img = IMAGEMANAGER->findImage("bigbandit_walk");
		if (info.direction == E_LEFT) _motion = bigbanditwalkleft;
		if (info.direction == E_RIGHT) _motion = bigbanditwalkright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
