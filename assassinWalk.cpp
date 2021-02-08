#include "stdafx.h"
#include "assassinWalk.h"

HRESULT assassinWalk::init(enemyinfo info)
{
	assassinwalkleft = new animation;
	assassinwalkleft->init("assassin_walk");
	assassinwalkleft->setPlayFrame(0, 5, false, true);
	assassinwalkleft->setFPS(10);

	assassinwalkright = new animation;					
	assassinwalkright->init("assassin_walk");			
	assassinwalkright->setPlayFrame(11, 6, false, true);	
	assassinwalkright->setFPS(10);						

	assassinhurtright = new animation;
	assassinhurtright->init("assassin_hurt");
	assassinhurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	assassinhurtright->setFPS(10);

	assassinhurtleft = new animation;
	assassinhurtleft->init("assassin_hurt");
	assassinhurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	assassinhurtleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("assassin_walk");
	if (info.direction == E_LEFT) _motion = assassinwalkleft;
	if (info.direction == E_RIGHT) _motion = assassinwalkright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void assassinWalk::update(enemyinfo & info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("assassin_hurt");
		if (info.direction == E_LEFT) _motion = assassinhurtleft;
		if (info.direction == E_RIGHT) _motion = assassinhurtright;
	}
	else
	{
		if (!MAPMANAGER->isCollisionTile(info.pt, info.width, info.height)) {
			info.pt.x += cosf(info.moveAngle)* info.speed;
			info.pt.y += -sinf(info.moveAngle)* info.speed;
		}

		_img = IMAGEMANAGER->findImage("assassin_walk");
		if (info.direction == E_LEFT) _motion = assassinwalkleft;
		if (info.direction == E_RIGHT) _motion = assassinwalkright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
