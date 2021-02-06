#include "stdafx.h"
#include "pistol.h"

HRESULT pistol::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("pistol");
	_pt = pt;
	_state = state;
	if (_state == NOWUSING) Position();
	else if (_state == ONGROUND)
	{
		_imgx = _pt.x;
		_imgy = _pt.y;
	}
	_type = PISTOL;
	_radius = 15;
	_damage = 5;
	_coolDown = 10;
	_coolCnt = _coolDown + PLAYERMANAGER->getPlayer()->getInterval();
	_angle = 0;
	_bulletSpd = 15;
	return S_OK;
}

void pistol::update()
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

void pistol::fire()
{
	if (_coolCnt >= _coolDown + PLAYERMANAGER->getPlayer()->getInterval() && PLAYERMANAGER->getPlayer()->getPlayerbullet() > 0)
	{
		BULLETMANAGER->PlayerFire(ANGLE1, _pt, _bulletSpd, _angle, _damage);
		PLAYERMANAGER->getPlayer()->setPlayerbullet(PLAYERMANAGER->getPlayer()->getPlayerbullet() - 1);
		_coolCnt = 0;
	}
}
