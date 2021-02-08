#include "stdafx.h"
#include "scolpionWalk.h"

HRESULT scolpionWalk::init(enemyinfo info)
{
	scolpionwalkright = new animation;
	scolpionwalkright->init("scolpion_walk");
	scolpionwalkright->setPlayFrame(0, 5, false, true);
	scolpionwalkright->setFPS(10);

	scolpionwalkleft = new animation;
	scolpionwalkleft->init("scolpion_walk");
	scolpionwalkleft->setPlayFrame(11, 6, false, true);
	scolpionwalkleft->setFPS(10);

	scolpionhurtright = new animation;
	scolpionhurtright->init("scolpion_hurt");
	scolpionhurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	scolpionhurtright->setFPS(10);

	scolpionhurtleft = new animation;
	scolpionhurtleft->init("scolpion_hurt");
	scolpionhurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	scolpionhurtleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("scolpion_walk");
	if (info.direction == E_LEFT) _motion = scolpionwalkleft;
	if (info.direction == E_RIGHT) _motion = scolpionwalkright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void scolpionWalk::update(enemyinfo & info)
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
		_img = IMAGEMANAGER->findImage("scolpion_hurt");
		if (info.direction == E_LEFT) _motion = scolpionhurtleft;
		if (info.direction == E_RIGHT) _motion = scolpionhurtright;
	}
	else
	{
		if (!MAPMANAGER->isCollisionTile(info.pt, info.width, info.height)) {
			info.pt.x += cosf(info.moveAngle)* info.speed;
			info.pt.y += -sinf(info.moveAngle)* info.speed;
		}
		_img = IMAGEMANAGER->findImage("scolpion_walk");
	
		if (PLAYERMANAGER->getPlayer()->getPt().x < info.pt.x)
		{
			info.direction == E_LEFT;
			_motion = scolpionwalkleft;

		}
		if (PLAYERMANAGER->getPlayer()->getPt().x > info.pt.x)
		{
			info.direction == E_RIGHT;
			_motion = scolpionwalkright;

		}

	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
