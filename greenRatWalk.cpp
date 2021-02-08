#include "stdafx.h"
#include "greenRatWalk.h"

HRESULT greenRatWalk::init(enemyinfo info)
{
	greenratwalkright = new animation;
	greenratwalkright->init("greenrat_walk");
	greenratwalkright->setPlayFrame(0, 5, false, true);
	greenratwalkright->setFPS(10);

	greenratwalkleft = new animation;
	greenratwalkleft->init("greenrat_walk");
	greenratwalkleft->setPlayFrame(11, 6, false, true);
	greenratwalkleft->setFPS(10);

	greenrathurtright = new animation;
	greenrathurtright->init("greenrat_hurt");
	greenrathurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	greenrathurtright->setFPS(10);

	greenrathurtleft = new animation;
	greenrathurtleft->init("greenrat_hurt");
	greenrathurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	greenrathurtleft->setFPS(10);

	_pt = info.pt;
	_img = IMAGEMANAGER->findImage("greenrat_walk");
	if (info.direction == E_LEFT) _motion = greenratwalkleft;
	if (info.direction == E_RIGHT)_motion = greenratwalkright;
	_motion->start();


	return S_OK;
}

void greenRatWalk::update(enemyinfo & info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		SOUNDMANAGER->play("¿¡³Ê¹ÌÈý2", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("greenrat_hurt");

		if (info.direction == E_LEFT) _motion = greenrathurtleft;
		if (info.direction == E_RIGHT)_motion = greenrathurtright;

	}
	else
	{
		if (!MAPMANAGER->isCollisionTile(info.pt, info.width, info.height)) {
			info.pt.x += cosf(info.moveAngle)* info.speed;
			info.pt.y += -sinf(info.moveAngle)* info.speed;
		}

		_img = IMAGEMANAGER->findImage("greenrat_walk");
	

		if (PLAYERMANAGER->getPlayer()->getPt().x < info.pt.x)
		{
			info.direction == E_LEFT;
			_motion = greenratwalkleft;

		}
		if (PLAYERMANAGER->getPlayer()->getPt().x > info.pt.x)
		{
			info.direction == E_RIGHT;
			_motion = greenratwalkright;

		}

	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
