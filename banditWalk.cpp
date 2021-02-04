#include "stdafx.h"
#include "banditWalk.h"




HRESULT banditWalk::init(enemyinfo info)
{
	banditwalkright = new animation;
	banditwalkright->init("bandit_walk");
	banditwalkright->setPlayFrame(0, 5, false, true);
	banditwalkright->setFPS(10);

	banditwalkleft = new animation;
	banditwalkleft->init("bandit_walk");
	banditwalkleft->setPlayFrame(11, 6, false, true);
	banditwalkleft->setFPS(10);

	bandithurtright = new animation;
	bandithurtright->init("bandit_hurt");
	bandithurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	bandithurtright->setFPS(10);

	bandithurtleft = new animation;
	bandithurtleft->init("bandit_hurt");
	bandithurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	bandithurtleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("bandit_walk");
	_motion = banditwalkright;
	_motion->start();
	_pt = info.pt;
	if (info.direction == E_LEFT)	_motion = banditwalkleft;
	if (info.direction == E_RIGHT)	_motion = banditwalkright;
	return S_OK;
}

void banditWalk::update(enemyinfo &info)
{
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	_pt = info.pt;
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("bandit_hurt");
		if (info.direction == E_LEFT) _motion = bandithurtleft;
		if (info.direction == E_RIGHT) _motion = bandithurtright;
	}
	else
	{
		/*info.pt.x += cosf(info.moveAngle)* info.speed;
		info.pt.y += -sinf(info.moveAngle)* info.speed;*/

		if (info.pt.x != MAPMANAGER->enemyMove(info.pt).x || info.pt.y != MAPMANAGER->enemyMove(info.pt).y) {
			if (info.pt.x < MAPMANAGER->enemyMove(info.pt).x) {
				info.pt.x++;
			}
			else {
				info.pt.x--;
			}

			if (info.pt.y < MAPMANAGER->enemyMove(info.pt).y) {
				info.pt.y++;
			}
			else {
				info.pt.y--;
			}
			
		}

		_img = IMAGEMANAGER->findImage("bandit_walk");
		if (info.direction == E_LEFT)
		{
			_motion = banditwalkleft;
		}
		if (info.direction == E_RIGHT)
		{
			_motion = banditwalkright;
		}
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);

}
