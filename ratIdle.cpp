#include "stdafx.h"
#include "ratIdle.h"

HRESULT ratIdle::init(enemyinfo info)
{

	ratidleright = new animation;
	ratidleright->init("rat_idle");
	ratidleright->setPlayFrame(0, 3, false, true);
	ratidleright->setFPS(10);

	ratidleleft = new animation;
	ratidleleft->init("rat_idle");
	ratidleleft->setPlayFrame(7, 4, false, true);
	ratidleleft->setFPS(10);

	rathurtright = new animation;
	rathurtright->init("rat_hurt");
	rathurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	rathurtright->setFPS(10);

	rathurtleft = new animation;
	rathurtleft->init("rat_hurt");
	rathurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	rathurtleft->setFPS(10);

	_pt = info.pt;
	_img = IMAGEMANAGER->findImage("rat_idle");
	if (info.direction == E_LEFT) _motion = ratidleleft;
	if (info.direction == E_RIGHT)_motion = ratidleright;
	_motion->start();

	return S_OK;
}

void ratIdle::update(enemyinfo & info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("rat_hurt");

		if (info.direction == E_LEFT) _motion = rathurtleft;
		if (info.direction == E_RIGHT)_motion = rathurtright;

	}
	else
	{
		_img = IMAGEMANAGER->findImage("rat_idle");
		if (info.direction == E_LEFT) _motion = ratidleleft;
		if (info.direction == E_RIGHT)_motion = ratidleright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
