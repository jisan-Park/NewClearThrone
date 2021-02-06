#include "stdafx.h"
#include "razerRifle.h"

HRESULT razerRifle::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("razerrifle");
	_pt = pt;
	_radius = 20;
	_state = state;
	if (_state == NOWUSING) Position();
	else if (_state == ONGROUND)
	{
		_imgx = _pt.x;
		_imgy = _pt.y;
	}
	_type = RAZERRIFLE;
	_damage = 5;
	_coolDown = 15;
	_bulletSpd = 30;
	_angle = 0;

	return S_OK;
}

void razerRifle::update()
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

void razerRifle::fire()
{
	if (_coolCnt >= _coolDown + PLAYERMANAGER->getPlayer()->getInterval() && PLAYERMANAGER->getPlayer()->getPlayerenergyb() > 0)
	{
		BULLETMANAGER->PlayerFire(ANGLE16, _pt, _bulletSpd, _angle, _damage);

		PLAYERMANAGER->getPlayer()->setPlayerenergyb(PLAYERMANAGER->getPlayer()->getPlayerenergyb() - 1);
		_coolCnt = 0;
	}
}
