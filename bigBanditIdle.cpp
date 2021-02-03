#include "stdafx.h"
#include "bigBanditIdle.h"


HRESULT bigBanditIdle::init(enemyinfo info)
{

	bigbanditidleright = new animation;
	bigbanditidleright->init("bigbandit_idle");
	bigbanditidleright->setPlayFrame(0, 5, false, true);
	bigbanditidleright->setFPS(10);

	bigbanditidleleft = new animation;
	bigbanditidleleft->init("bandit_idle");
	bigbanditidleleft->setPlayFrame(11, 6, false, true);
	bigbanditidleleft->setFPS(10);

	bigbandithurtright = new animation;
	bigbandithurtright->init("bigbandit_hurt");
	bigbandithurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	bigbandithurtright->setFPS(10);

	bigbandithurtleft = new animation;
	bigbandithurtleft->init("bigbandit_hurt");
	bigbandithurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	bigbandithurtleft->setFPS(10);

	_pt = info.pt;
	_img = IMAGEMANAGER->findImage("bigbandit_idle");
	if (info.direction == E_LEFT) _motion = bigbanditidleleft;
	if (info.direction == E_RIGHT) _motion = bigbanditidleright;
	_motion->start();
	return S_OK;
}

void bigBanditIdle::update(enemyinfo & info)
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
		_img = IMAGEMANAGER->findImage("bigbandit_idle");
		if (info.direction == E_LEFT) _motion = bigbanditidleleft;
		if (info.direction == E_RIGHT) _motion = bigbanditidleright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
