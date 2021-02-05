#include "stdafx.h"
#include "pistol.h"

HRESULT pistol::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("pistol");
	_pt = pt;
	_state = state;
	if (_state == NOWUSING) Position();
	else if (_state == ONGROUND)
	{
		_imgx = _pt.x;
		_imgy = _pt.y;
	}
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
	setFrameIndex(_angle);
	if (_state == NOWUSING)
	{
		_pt = PLAYERMANAGER->getPlayer()->getPt();
		Position();
	}
	_bullet->update();
}

void pistol::fire()
{
	_bullet->fire(_pt, _bulletSpd, _angle, PLAYER);
}
