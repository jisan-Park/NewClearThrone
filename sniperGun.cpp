#include "stdafx.h"
#include "sniperGun.h"

HRESULT sniperGun::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("bandit_gun");
	_pt = pt;
	_state = state;
	_radius = 15;
	_damage = 2;
	_coolDown = 50;
	_angle = 0;
	_bulletSpd =5;
	return S_OK;
}

void sniperGun::update()
{
	Position();
	setFrameIndex8(_angle);
}

void sniperGun::fire()
{
	for (int i = 0; i < 3; i++)
	{
		BULLETMANAGER->EnemyFire(E_ANGLE16_1, _pt, _bulletSpd, _angle - 0.2f + 0.1f * i, _damage);
	}
}