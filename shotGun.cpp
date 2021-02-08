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
	_coolDown = 20;
	_coolCnt = _coolDown + PLAYERMANAGER->getPlayer()->getInterval();
	_bulletSpd = 25;
	_angle = 0;

	return S_OK;
}

void shotGun::update()
{
	setFrameIndex(_angle);
	if (_coolCnt <= _coolDown + PLAYERMANAGER->getPlayer()->getInterval()) _coolCnt++; // = TIMEMANAGER->getElapsedTime();
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

void shotGun::fire()
{
	if (_coolCnt >= _coolDown + PLAYERMANAGER->getPlayer()->getInterval() && PLAYERMANAGER->getPlayer()->getPlayershellb() > 0)
	{
		for (int i = 0; i < 5; i++)
		{
			if (PLAYERMANAGER->getPlayer()->getPlayershellb() <= 0) break;
			BULLETMANAGER->PlayerFire(SHOTGUNBULLET, _pt, _bulletSpd, _angle - 0.2f + 0.1f * i, _damage);
			PLAYERMANAGER->getPlayer()->setPlayershellb(PLAYERMANAGER->getPlayer()->getPlayershellb() - 1);
		}
		_coolCnt = 0;
	}
}
