#include "stdafx.h"
#include "salamanderWalk.h"

HRESULT salamanderWalk::init(enemyinfo info)
{
	salamanderwalkright = new animation;
	salamanderwalkright->init("salamander_walk");
	salamanderwalkright->setPlayFrame(0, 7, false, true);
	salamanderwalkright->setFPS(10);

	salamanderwalkleft = new animation;
	salamanderwalkleft->init("salamander_walk");
	salamanderwalkleft->setPlayFrame(15, 8, false, true);
	salamanderwalkleft->setFPS(10);

	salamanderhurtright = new animation;
	salamanderhurtright->init("salamander_hurt");
	salamanderhurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	salamanderhurtright->setFPS(10);

	salamanderhurtleft = new animation;
	salamanderhurtleft->init("salamander_hurt");
	salamanderhurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	salamanderhurtleft->setFPS(10);
	_img = IMAGEMANAGER->findImage("salamander_walk");
	if (info.direction == E_LEFT) _motion = salamanderwalkleft;
	if (info.direction == E_RIGHT) _motion = salamanderwalkright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void salamanderWalk::update(enemyinfo & info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("salamander_hurt");
		if (info.direction == E_LEFT) _motion = salamanderhurtleft;
		if (info.direction == E_RIGHT) _motion = salamanderhurtright;
	}
	else
	{
		if (!MAPMANAGER->isCollisionTile(info.pt, info.width, info.height)) {
			info.pt.x += cosf(info.moveAngle)* info.speed;
			info.pt.y += -sinf(info.moveAngle)* info.speed;
		}
		_img = IMAGEMANAGER->findImage("salamander_walk");

		if (PLAYERMANAGER->getPlayer()->getPt().x < info.pt.x)
		{
			info.direction == E_LEFT;
			_motion = salamanderwalkleft;

		}
		if (PLAYERMANAGER->getPlayer()->getPt().x > info.pt.x)
		{
			info.direction == E_RIGHT;
			_motion = salamanderwalkright;

		}

	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
