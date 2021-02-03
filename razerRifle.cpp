#include "stdafx.h"
#include "razerRifle.h"

HRESULT razerRifle::init(POINT pt)
{
	_img = IMAGEMANAGER->findImage("razerrifle");
	_pt = pt;
	//setWH();
	_hwidth = 30;
	_hheight = 30;
	_state = NOWUSING;
	_type = RAZERRIFLE;
	_damage = 5;
	_coolDown = 3;
	_angle = 0;

	return S_OK;
}

void razerRifle::update()
{
	setFrameIndex(_angle);
}
