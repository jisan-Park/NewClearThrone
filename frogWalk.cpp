#include "stdafx.h"
#include "frogWalk.h"

HRESULT frogWalk::init(enemyinfo info)
{
	frogwalkright = new animation;
	frogwalkright->init("frog_walk");
	frogwalkright->setPlayFrame(0, 5, false, true);
	frogwalkright->setFPS(10);

	frogwalkleft = new animation;
	frogwalkleft->init("frog_walk");
	frogwalkleft->setPlayFrame(11, 6, false, true);
	frogwalkleft->setFPS(10);

	froghurtright = new animation;
	froghurtright->init("frog_hurt");
	froghurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	froghurtright->setFPS(10);

	froghurtleft = new animation;
	froghurtleft->init("frog_hurt");
	froghurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	froghurtleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("frog_walk");
	if (info.direction == E_LEFT) _motion = frogwalkleft;
	if (info.direction == E_RIGHT)_motion = frogwalkright;
	_motion->start();
	_pt = info.pt;

	return S_OK;
}

void frogWalk::update(enemyinfo & info)
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
		if (!MAPMANAGER->isCollisionTile(info.pt, info.width, info.height)) {
			info.pt.x += cosf(info.moveAngle)* info.speed;
			info.pt.y += -sinf(info.moveAngle)* info.speed;
		}
		_img = IMAGEMANAGER->findImage("frog_walk");

		if (PLAYERMANAGER->getPlayer()->getPt().x < info.pt.x)
		{
			info.direction == E_LEFT;
			_motion = frogwalkleft;

		}
		if (PLAYERMANAGER->getPlayer()->getPt().x > info.pt.x)
		{
			info.direction == E_RIGHT;
			_motion = frogwalkright;

		}

	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
