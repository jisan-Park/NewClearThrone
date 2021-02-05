#include "stdafx.h"
#include "wrench.h"

HRESULT wrench::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("wrench");
	_pt = pt;
	_radius = 20;
	_state = state;
	_type = ASSULTRIFLE;
	_damage = 5;
	_coolDown = 3;
	_angle = 0;

	return S_OK;
}

void wrench::update()
{
	setFrameIndex(_angle);
}
