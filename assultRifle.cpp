#include "stdafx.h"
#include "assultRifle.h"

HRESULT assultRifle::init(POINT pt)
{
	_img = IMAGEMANAGER->findImage("assultrifle");
	_pt = pt;
	//setWH();
	_hwidth = 30;
	_hheight = 30;
	_state = NOWUSING;
	_type = ASSULTRIFLE;
	_damage = 5;
	_coolDown = 3;
	_angle = 0;

	return S_OK;
}

void assultRifle::update()
{
	setFrameIndex(_angle);
}
