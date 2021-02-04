#include "stdafx.h"
#include "pistol.h"

HRESULT pistol::init(POINT pt)
{
	_img = IMAGEMANAGER->findImage("pistol");
	_pt = pt;
	_state = NOWUSING;
	_type = PISTOL;
	_radius = 15;
	_damage = 5;
	_coolDown = 3;
	_angle = 0;
	_bulletSpd = 15;
	_bullet = new bullet1;
	_bullet->init();
	return S_OK;
}

void pistol::update()
{
	Position();
	setFrameIndex(_angle);
	_pt = PLAYERMANAGER->getPlayer()->getPt();
	_bullet->update();
}

void pistol::fire()
{
	_bullet->fire(_pt, _bulletSpd, _angle, PLAYER);
}
