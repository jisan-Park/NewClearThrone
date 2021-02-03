#include "stdafx.h"
#include "shotGun.h"

HRESULT shotGun::init(POINT pt)
{
	_img = IMAGEMANAGER->findImage("shotgun");
	_pt = pt;
	//setWH();
	_hwidth = 30;
	_hheight = 30;
	_state = NOWUSING;
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
