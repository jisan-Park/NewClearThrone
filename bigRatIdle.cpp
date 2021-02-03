#include "stdafx.h"
#include "bigRatIdle.h"


HRESULT bigRatIdle::init(enemyinfo info)
{
	bigratidleright = new animation;
	bigratidleright->init("bigrat_idle");
	bigratidleright->setPlayFrame(0, 1, false, true);
	bigratidleright->setFPS(10);

	bigratidleright = new animation;
	bigratidleright->init("bigrat_idle");
	bigratidleright->setPlayFrame(3, 2, false, true);
	bigratidleright->setFPS(10);

	bigrathurtright = new animation;
	bigrathurtright->init("bigrat_hurt");
	bigrathurtright->setPlayFrame(0, 2, false, false, hurtFinish,this);
	bigrathurtright->setFPS(10);

	bigrathurtleft = new animation;
	bigrathurtleft->init("bigrat_hurt");
	bigrathurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	bigrathurtleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("bigrat_idle");
	if (info.direction == E_LEFT) _motion = bigratidleright;
	if (info.direction == E_RIGHT)_motion = bigratidleright;
	_pt = info.pt;

	return S_OK;
}

void bigRatIdle::update(enemyinfo & info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	if (isHurt == true)
	{

		_img = IMAGEMANAGER->findImage("bigrat_hurt");
		if (info.direction == E_LEFT) _motion = bigrathurtleft;
		if (info.direction == E_RIGHT)_motion = bigrathurtright;
	}
	else
	{
		_img = IMAGEMANAGER->findImage("bigrat_idle");
		if (info.direction == E_LEFT) _motion = bigratidleright;
		if (info.direction == E_RIGHT)_motion = bigratidleright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
