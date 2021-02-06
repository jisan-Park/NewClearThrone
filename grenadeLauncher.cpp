#include "stdafx.h"
#include "grenadeLauncher.h"

HRESULT grenadeLauncher::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("grenadelauncher");
	_pt = pt;
	_state = state;
	if (_state == NOWUSING) Position();
	else if (_state == ONGROUND)
	{
		_imgx = _pt.x;
		_imgy = _pt.y;
	}
	_type = GRENADELAUNCHER;
	_radius = 20;
	_damage = 5;
	_coolDown = 3;
	_angle = 0;
	_bulletSpd = 5;
	return S_OK;
}

void grenadeLauncher::update()
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

void grenadeLauncher::fire()
{
	BULLETMANAGER->fire(ANGLE1, _pt, _bulletSpd, _angle, _damage, PLAYER);
	SOUNDMANAGER->play("ÀçÀåÀü", GAMEMANAGER->getSfxVolume());
}
