#include "stdafx.h"
#include "gatorWalk.h"

HRESULT gatorWalk::init(enemyinfo info)
{
	gatorwalkright = new animation;
	gatorwalkright->init("gator_walk");
	gatorwalkright->setPlayFrame(0, 5, false, true);
	gatorwalkright->setFPS(10);

	gatorwalkleft = new animation;
	gatorwalkleft->init("gator_walk");
	gatorwalkleft->setPlayFrame(11, 6, false, true);
	gatorwalkleft->setFPS(10);

	gatorhurtright = new animation;
	gatorhurtright->init("gator_hurt");
	gatorhurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	gatorhurtright->setFPS(10);

	gatorhurtleft = new animation;
	gatorhurtleft->init("gator_hurt");
	gatorhurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	gatorhurtleft->setFPS(10);

	_pt = info.pt;
	_img = IMAGEMANAGER->findImage("gator_walk");
	if (info.direction == E_LEFT) _motion = gatorwalkleft;
	if (info.direction == E_RIGHT)_motion = gatorwalkright;
	_motion->start();

	return S_OK;
}

void gatorWalk::update(enemyinfo & info)
{

	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("gator_hurt");
		if (info.direction == E_LEFT) _motion = gatorhurtleft;
		if (info.direction == E_RIGHT)_motion = gatorhurtright;

	}
	else
	{
		info.pt.x += cosf(info.moveAngle)* info.speed;
		info.pt.y += -sinf(info.moveAngle)* info.speed;
		_img = IMAGEMANAGER->findImage("gator_walk");
		if (PLAYERMANAGER->getPlayer()->getPt().x < info.pt.x)
		{
			info.direction == E_LEFT;
			_motion = gatorwalkleft;

		}
		if (PLAYERMANAGER->getPlayer()->getPt().x > info.pt.x)
		{
			info.direction == E_RIGHT;
			_motion = gatorwalkright;

		}
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
