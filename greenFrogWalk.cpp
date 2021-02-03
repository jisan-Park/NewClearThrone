#include "stdafx.h"
#include "greenFrogWalk.h"

HRESULT greenFrogWalk::init(enemyinfo info)
{
	greenfrogwalkright = new animation;
	greenfrogwalkright->init("greenfrog_walk");
	greenfrogwalkright->setPlayFrame(0, 5, false, true);
	greenfrogwalkright->setFPS(10);

	greenfrogwalkleft = new animation;
	greenfrogwalkleft->init("greenfrog_walk");
	greenfrogwalkleft->setPlayFrame(11, 6, false, true);
	greenfrogwalkleft->setFPS(10);

	greenfroghurtright = new animation;
	greenfroghurtright->init("greenfrog_hurt");
	greenfroghurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	greenfroghurtright->setFPS(10);

	greenfroghurtleft = new animation;
	greenfroghurtleft->init("greenfrog_hurt");
	greenfroghurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	greenfroghurtleft->setFPS(10);

	_pt = info.pt;

	_img = IMAGEMANAGER->findImage("greenfrog_walk");
	if (info.direction == E_LEFT) _motion = greenfrogwalkleft;
	if (info.direction == E_RIGHT)_motion = greenfrogwalkright;
	_motion->start();


	return S_OK;
}

void greenFrogWalk::update(enemyinfo & info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("greenfrog_hurt");
		if (info.direction == E_LEFT) _motion = greenfroghurtleft;
		if (info.direction == E_RIGHT)_motion = greenfroghurtright;

	}
	else
	{
		_img = IMAGEMANAGER->findImage("greenfrog_walk");
		if (info.direction == E_LEFT) _motion = greenfrogwalkleft;
		if (info.direction == E_RIGHT)_motion = greenfrogwalkright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
