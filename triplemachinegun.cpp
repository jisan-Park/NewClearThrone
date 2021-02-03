#include "stdafx.h"
#include "triplemachinegun.h"

HRESULT triplemachinegun::init(POINT pt)
{
	_img = IMAGEMANAGER->findImage("triplemachinegun");
	_pt = pt;
	_radius = 20;
	_state = NOWUSING;
	_type = ASSULTRIFLE;
	_damage = 5;
	_coolDown = 3;
	_angle = 0;

	return S_OK;
}

void triplemachinegun::update()
{
	setFrameIndex(_angle);
}
