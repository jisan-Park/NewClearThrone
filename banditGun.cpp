#include "stdafx.h"
#include "banditGun.h"

HRESULT banditGun::init(POINT pt)
{
	_img = IMAGEMANAGER->findImage("bandit_gun");
	_pt = pt;
	_state = NOWUSING;
	_radius = 15;
	_damage = 5;
	_coolDown = 50;
	_angle = 0;
	_bulletSpd = 15;
	_bullet = new bullet1;
	_bullet->init();
	return S_OK;
}

void banditGun::update()
{
	Position();
	setFrameIndex8(_angle);
	_bullet->update();
}

void banditGun::fire()
{
	_bullet->fire(_pt, _bulletSpd, _angle, ENEMY);
}
