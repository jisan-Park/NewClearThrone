#include "stdafx.h"
#include "sword.h"

HRESULT sword::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("sword");
	_pt = pt;
	_radius = 20;
	_state = state;
	_type = ASSULTRIFLE;
	_damage = 5;
	_coolDown = 3;
	_angle = 0;

	return S_OK;
}

void sword::update()
{
	setFrameIndex(_angle);
}
