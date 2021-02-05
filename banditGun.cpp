#include "stdafx.h"
#include "banditGun.h"

HRESULT banditGun::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("bandit_gun");
	_pt = pt;
	_state = state;
	_radius = 15;
	_damage = 5;
	_coolDown = 50;
	_angle = 0;
	_bulletSpd = 15;
	return S_OK;
}

void banditGun::update()
{
	Position();
	setFrameIndex8(_angle);
}

void banditGun::fire()
{
	BULLETMANAGER->fire(ANGLE1, _pt, _bulletSpd, _angle, _damage, ENEMY);
}
