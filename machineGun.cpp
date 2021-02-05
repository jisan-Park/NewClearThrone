#include "stdafx.h"
#include "machineGun.h"

HRESULT machineGun::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("machinegun");
	_pt = pt;
	_radius = 20;
	_state = state;
	_type = MACHINEGUN;
	_damage = 5;
	_coolDown = 3;
	_angle = 0;

	return S_OK;
}

void machineGun::update()
{
	setFrameIndex(_angle);
}
