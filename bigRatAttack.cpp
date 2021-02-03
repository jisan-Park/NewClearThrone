#include "stdafx.h"
#include "bigRatAttack.h"


HRESULT bigRatAttack::init(enemyinfo info)
{
	
	bigratattackright = new animation;
	bigratattackright->init("bigrat_attack");
	bigratattackright->setPlayFrame(0, 4, false, false);
	bigratattackright->setFPS(10);

	bigratattackleft = new animation;
	bigratattackleft->init("bigrat_attack");
	bigratattackleft->setPlayFrame(8, 5, false, false);
	bigratattackleft->setFPS(10);

	bigrathurtright = new animation;
	bigrathurtright->init("bigrat_hurt");
	bigrathurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	bigrathurtright->setFPS(10);

	bigrathurtleft = new animation;
	bigrathurtleft->init("bigrat_hurt");
	bigrathurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	bigrathurtleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("bigrat_attack");
	if (info.direction == E_LEFT) _motion = bigratattackleft;
	if (info.direction == E_RIGHT)_motion = bigratattackright;
	_motion->start();
	_pt = info.pt;

	return S_OK;
}

void bigRatAttack::update(enemyinfo & info)
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
		_img = IMAGEMANAGER->findImage("bigrat_attack");
		if (info.direction == E_LEFT) _motion = bigratattackleft;
		if (info.direction == E_RIGHT)_motion = bigratattackright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
