#include "stdafx.h"
#include "triplemachinegun.h"

HRESULT triplemachinegun::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("triplemachinegun");
	_pt = pt;
	_radius = 20;
	_state = state;
	if (_state == NOWUSING) Position();
	else if (_state == ONGROUND)
	{
		_imgx = _pt.x;
		_imgy = _pt.y;
	}
	_type = TRIPLEMACHINEGUN;
	_damage = 5;
	_coolDown = 3;
	_bulletSpd = 15;
	_angle = 0;

	return S_OK;
}

void triplemachinegun::update()
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

void triplemachinegun::fire()
{
	BULLETMANAGER->fire(ANGLE16, _pt, _bulletSpd, _angle, _damage, ENEMY);
	SOUNDMANAGER->play("¾àÇÑÃÑ", (GAMEMANAGER->getSfxVolume() / 100.0f)*1.0f);
}
