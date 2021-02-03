#include "stdafx.h"
#include "pistol.h"

HRESULT pistol::init(POINT pt)
{
	_img = IMAGEMANAGER->findImage("pistol");
	_pt = pt;
	//setWH();
	_hwidth = 30;
	_hheight = 30;
	_state = NOWUSING;
	_type = PISTOL;
	_damage = 5;
	_coolDown = 3;
	_angle = 0;

	return S_OK;
}

void pistol::update()
{
	setFrameIndex(_angle);
	_pt = PLAYERMANAGER->getPlayer()->getPt();
}
