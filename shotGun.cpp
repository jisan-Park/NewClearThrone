#include "stdafx.h"
#include "shotGun.h"

HRESULT shotGun::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("shotgun");
	_pt = pt;
	_radius = 20;
	_state = state;
	_type = SHOTGUN;
	_damage = 5;
	_coolDown = 3;
	_angle = 0;

	return S_OK;
}

void shotGun::update()
{
	setFrameIndex(_angle);
}
