#include "stdafx.h"
#include "bigRatWalk.h"


HRESULT bigRatWalk::init(enemyinfo info)
{

	bigratwalkright = new animation;
	bigratwalkright->init("bigrat_walk");
	bigratwalkright->setPlayFrame(0, 7, false, true);
	bigratwalkright->setFPS(10);

	bigratwalkleft = new animation;
	bigratwalkleft->init("bigrat_walk");
	bigratwalkleft->setPlayFrame(15, 8, false, true);
	bigratwalkleft->setFPS(10);


	bigrathurtright = new animation;
	bigrathurtright->init("bigrat_hurt");
	bigrathurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	bigrathurtright->setFPS(10);

	bigrathurtleft = new animation;
	bigrathurtleft->init("bigrat_hurt");
	bigrathurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	bigrathurtleft->setFPS(10);


	_img = IMAGEMANAGER->findImage("bigrat_walk");
	if (info.direction == E_LEFT) _motion = bigratwalkleft;
	if (info.direction == E_RIGHT)_motion = bigratwalkright;
	_motion->start();
	_pt = info.pt;

	return S_OK;
}

void bigRatWalk::update(enemyinfo & info)
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
		_img = IMAGEMANAGER->findImage("bigrat_walk");

		info.pt.x += cosf(info.moveAngle)* info.speed;
		info.pt.y += -sinf(info.moveAngle)* info.speed;

		if (PLAYERMANAGER->getPlayer()->getPt().x < info.pt.x)
		{
			info.direction == E_LEFT;
			_motion = bigratwalkleft;
			_motion->start();
		}
		if (PLAYERMANAGER->getPlayer()->getPt().x > info.pt.x)
		{
			info.direction == E_RIGHT;
			_motion = bigratwalkright;
			_motion->start();
		}

	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
