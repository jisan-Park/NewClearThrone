#include "stdafx.h"
#include "assultRifle.h"

HRESULT assultRifle::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("assultrifle");
	_pt = pt;
	_state = state;
	if (_state == NOWUSING) Position();
	else if (_state == ONGROUND)
	{
		_imgx = _pt.x;
		_imgy = _pt.y;
	}
	_type = ASSULTRIFLE;
	_damage = 7;
	_radius = 20;
	_coolDown = 3;
	_angle = 0;
	_bulletSpd = 15;
	return S_OK;
}

void assultRifle::update()
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

void assultRifle::fire()
{
	SOUNDMANAGER->play("¾àÇÑÃÑ", (GAMEMANAGER->getSfxVolume() / 100.0f)*1.0f);
	BULLETMANAGER->fire(ANGLE16, _pt, _bulletSpd, _angle, _damage, PLAYER);
}
