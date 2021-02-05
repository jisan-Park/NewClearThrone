#include "stdafx.h"
#include "grenadeLauncher.h"

HRESULT grenadeLauncher::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("grenadelauncher");
	_pt = pt;
	_state = state;
	_type = GRENADELAUNCHER;
	_radius = 20;
	_damage = 5;
	_coolDown = 3;
	_angle = 0;
	return S_OK;
}

void grenadeLauncher::update()
{
	setFrameIndex(_angle);
}
