#include "stdafx.h"
#include "maggotIdle.h"

HRESULT maggotIdle::init(enemyinfo info)
{
	maggotidleright = new animation;
	maggotidleright->init("maggot_idle");
	maggotidleright->setPlayFrame(0, 3, false, true);
	maggotidleright->setFPS(10);

	maggotidleleft = new animation;
	maggotidleleft->init("maggot_idle");
	maggotidleleft->setPlayFrame(7, 4, false, true);
	maggotidleleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("maggot_idle");
	if (info.direction == E_LEFT) _motion = maggotidleleft;
	if (info.direction == E_RIGHT) _motion = maggotidleright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void maggotIdle::update(enemyinfo & info)
{
	_pt = info.pt;
	if (!MAPMANAGER->isCollisionTile(info.pt, info.width, info.height)) {
		info.pt.x += cosf(info.moveAngle)* info.speed;
		info.pt.y += -sinf(info.moveAngle)* info.speed;
	}

	_img = IMAGEMANAGER->findImage("maggot_idle");

	if (PLAYERMANAGER->getPlayer()->getPt().x < info.pt.x)
	{
		info.direction == E_LEFT;
		_motion = maggotidleleft;
		_motion->start();
	}
	if (PLAYERMANAGER->getPlayer()->getPt().x > info.pt.x)
	{
		info.direction == E_RIGHT;
		_motion = maggotidleright;
		_motion->start();
	}
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
