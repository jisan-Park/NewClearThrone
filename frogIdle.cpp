#include "stdafx.h"
#include "frogIdle.h"


HRESULT frogIdle::init(enemyinfo info)
{
	frogidleright = new animation;
	frogidleright->init("frog_idle");
	frogidleright->setPlayFrame(0, 3, false, true);
	frogidleright->setFPS(10);

	frogidleleft = new animation;
	frogidleleft->init("frog_idle");
	frogidleleft->setPlayFrame(6, 4, false, true);
	frogidleleft->setFPS(10);


	froghurtright = new animation;
	froghurtright->init("frog_hurt");
	froghurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	froghurtright->setFPS(10);

	froghurtleft = new animation;
	froghurtleft->init("frog_hurt");
	froghurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	froghurtleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("frog_idle");
	if (info.direction == E_LEFT) _motion = frogidleleft;
	if (info.direction == E_RIGHT)_motion = frogidleright;
	_motion->start();
	_pt = info.pt;


	return S_OK;
}

void frogIdle::update(enemyinfo & info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("frog_hurt");
		if (info.direction == E_LEFT) _motion = froghurtleft;
		if (info.direction == E_RIGHT)_motion = froghurtright;
	}
	else
	{
		_img = IMAGEMANAGER->findImage("frog_idle");
		if (info.direction == E_LEFT) _motion = frogidleleft;
		if (info.direction == E_RIGHT)_motion = frogidleright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
