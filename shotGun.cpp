#include "stdafx.h"
#include "shotGun.h"

HRESULT shotGun::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("shotgun");
	_pt = pt;
	_radius = 20;
	_state = state;
	_type = SHOTGUN;
	if (_state == NOWUSING) Position();
	else if (_state == ONGROUND)
	{
		_imgx = _pt.x;
		_imgy = _pt.y;
	}
	_damage = 5;
	_coolDown = 3;
	_bulletSpd = 17;
	_angle = 0;

	return S_OK;
}

void shotGun::update()
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
