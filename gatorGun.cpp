#include "stdafx.h"
#include "gatorGun.h"

HRESULT gatorGun::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("gator_gun");
	_pt = pt;
	_state = state;
	_radius = 15;
	_damage = 5;
	_coolDown = 50;
	_angle = 0;
	_bulletSpd = 10;
	return S_OK;
}

void gatorGun::update()
{
	Position();
	setFrameIndex8(_angle);
}

void gatorGun::fire()
{
	BULLETMANAGER->EnemyFire(E_SHOTGUN, _pt, _bulletSpd, _angle, _damage);
}
