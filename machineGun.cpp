#include "stdafx.h"
#include "machineGun.h"

HRESULT machineGun::init(POINT pt)
{
	_img = IMAGEMANAGER->findImage("machinegun");
	_pt = pt;
	//setWH();
	_hwidth = 30;
	_hheight = 30;
	_state = NOWUSING;
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
