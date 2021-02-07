#include "stdafx.h"
#include "ratWalk.h"

HRESULT ratWalk::init(enemyinfo info)
{
	ratwalkright = new animation;
	ratwalkright->init("rat_walk");
	ratwalkright->setPlayFrame(0, 5, false, true);
	ratwalkright->setFPS(10);

	ratwalkleft = new animation;
	ratwalkleft->init("rat_walk");
	ratwalkleft->setPlayFrame(11, 6, false, true);
	ratwalkleft->setFPS(10);

	rathurtright = new animation;
	rathurtright->init("rat_hurt");
	rathurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	rathurtright->setFPS(10);

	rathurtleft = new animation;
	rathurtleft->init("rat_hurt");
	rathurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	rathurtleft->setFPS(10);

	_pt = info.pt;
	_img = IMAGEMANAGER->findImage("rat_walk");
	if (info.direction == E_LEFT) _motion = ratwalkleft;
	if (info.direction == E_RIGHT)_motion = ratwalkright;
	_motion->start();

	return S_OK;
}

void ratWalk::update(enemyinfo & info)
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
		info.pt.x += cosf(info.moveAngle)* info.speed;
		info.pt.y += -sinf(info.moveAngle)* info.speed;
		
		_img = IMAGEMANAGER->findImage("rat_walk");
	
		if (PLAYERMANAGER->getPlayer()->getPt().x < info.pt.x)
		{
			info.direction == E_LEFT;
			_motion = ratwalkleft;

		}
		if (PLAYERMANAGER->getPlayer()->getPt().x > info.pt.x)
		{
			info.direction == E_RIGHT;
			_motion = ratwalkright;

		}

	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
