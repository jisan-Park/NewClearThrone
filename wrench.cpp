#include "stdafx.h"
#include "wrench.h"

HRESULT wrench::init(POINT pt)
{
	_img = IMAGEMANAGER->findImage("wrench");
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

void wrench::update()
{
	setFrameIndex(_angle);
}
