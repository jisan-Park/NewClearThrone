#include "stdafx.h"
#include "greenRatIdle.h"

HRESULT greenRatIdle::init(enemyinfo info)
{

	greenratidleright = new animation;
	greenratidleright->init("greenrat_idle");
	greenratidleright->setPlayFrame(0, 3, false, true);
	greenratidleright->setFPS(10);

	greenratidleleft = new animation;
	greenratidleleft->init("greenrat_idle");
	greenratidleleft->setPlayFrame(7, 4, false, true);
	greenratidleleft->setFPS(10);


	greenrathurtright = new animation;
	greenrathurtright->init("greenrat_hurt");
	greenrathurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	greenrathurtright->setFPS(10);

	greenrathurtleft = new animation;
	greenrathurtleft->init("greenrat_hurt");
	greenrathurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	greenrathurtleft->setFPS(10);

	_pt = info.pt;

	_img = IMAGEMANAGER->findImage("greenrat_idle");
	if (info.direction == E_LEFT) _motion = greenratidleleft;
	if (info.direction == E_RIGHT)_motion = greenratidleright;
	_motion->start();

	return S_OK;
}

void greenRatIdle::update(enemyinfo & info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("greenrat_hurt");

		if (info.direction == E_LEFT) _motion = greenrathurtleft;
		if (info.direction == E_RIGHT)_motion = greenrathurtright;

	}
	else
	{
		_img = IMAGEMANAGER->findImage("greenrat_idle");
		if (info.direction == E_LEFT) _motion = greenratidleleft;
		if (info.direction == E_RIGHT)_motion = greenratidleright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
