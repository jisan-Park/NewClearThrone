#include "stdafx.h"
#include "assultRifle.h"

HRESULT assultRifle::init(POINT pt)
{
	_img = IMAGEMANAGER->findImage("assultrifle");
	_pt = pt;
	_state = NOWUSING;
	_type = ASSULTRIFLE;
	_damage = 5;
	_radius = 20;
	_coolDown = 3;
	_angle = 0;

	return S_OK;
}

void assultRifle::update()
{
	setFrameIndex(_angle);
}
