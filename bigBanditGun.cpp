#include "stdafx.h"
#include "bigBanditGun.h"

HRESULT bigBanditGun::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("bigbandit_gun");
	_pt = pt;
	_state = state;
	_radius = 15;
	_damage = 5;
	_coolDown = 50;
	_angle = 0;
	_bulletSpd = 15;
	return S_OK;
}

void bigBanditGun::update()
{
	Position();
	setFrameIndex8(_angle);
}

void bigBanditGun::fire()
{
	BULLETMANAGER->EnemyFire(E_ANGLE16_1, _pt, _bulletSpd, _angle, _damage);
}