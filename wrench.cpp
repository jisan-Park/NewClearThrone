#include "stdafx.h"
#include "wrench.h"

HRESULT wrench::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("wrench");
	_pt = pt;
	_radius = 20;
	_state = state;
	if (_state == NOWUSING) Position();
	else if (_state == ONGROUND)
	{
		_imgx = _pt.x;
		_imgy = _pt.y;
	}
	_type = WRENCH;
	_damage = 5;
	_coolDown = 3;
	_angle = 0;
	_bulletSpd = 1;

	return S_OK;
}

void wrench::update()
{
	setFrameIndex(_angle);
	if (_state != ONGROUND)
	{
		_pt = PLAYERMANAGER->getPlayer()->getPt();
		if (_state == NOWUSING) Position();
		if (_state == READYTOUSE)
		{
			_imgx = _pt.x;
			_imgy = _pt.y;
		}
	}
}
