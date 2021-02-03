#include "stdafx.h"
#include "shovel.h"

HRESULT shovel::init(POINT pt)
{
	_img = IMAGEMANAGER->findImage("shovel");
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

void shovel::update()
{
	setFrameIndex(_angle);
}
