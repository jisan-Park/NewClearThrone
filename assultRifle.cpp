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
	_coolDown = 15;
	_coolCnt = _coolDown + PLAYERMANAGER->getPlayer()->getInterval();
	_angle = 0;
	_bulletSpd = 15;
	return S_OK;
}

void assultRifle::update()
{
	setFrameIndex(_angle);
	if (_coolCnt <= _coolDown + PLAYERMANAGER->getPlayer()->getInterval()) _coolCnt++; // = TIMEMANAGER->getElapsedTime();
	if (_fired == true)
	{
		_cnt++;
		if (_cnt % 6 == 0) followingFire();
		if (_cnt > 12)
		{
			_cnt = 0;
			_fired = false;
		}
	}
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
	if (_coolCnt >= _coolDown + PLAYERMANAGER->getPlayer()->getInterval() && PLAYERMANAGER->getPlayer()->getPlayerbullet() > 0)
	{
		if (_fired == false) _fired = true;
		BULLETMANAGER->PlayerFire(ANGLE16, _pt, _bulletSpd, _angle + RND->getFromFloatTo(-(_rndSpreadAngle - 0.01 * PLAYERMANAGER->getPlayer()->getAngleCard()), (_rndSpreadAngle - 0.01 * PLAYERMANAGER->getPlayer()->getAngleCard())), _damage);

		PLAYERMANAGER->getPlayer()->setPlayerbullet(PLAYERMANAGER->getPlayer()->getPlayerbullet() - 1);
		_coolCnt = 0;
	}
}

void assultRifle::followingFire()
{
	if (PLAYERMANAGER->getPlayer()->getPlayerbullet() > 0)
	{
		BULLETMANAGER->PlayerFire(ANGLE16, _pt, _bulletSpd, _angle + RND->getFromFloatTo(-(_rndSpreadAngle - 0.01 * PLAYERMANAGER->getPlayer()->getAngleCard()), (_rndSpreadAngle - 0.01 * PLAYERMANAGER->getPlayer()->getAngleCard())), _damage);
		PLAYERMANAGER->getPlayer()->setPlayerbullet(PLAYERMANAGER->getPlayer()->getPlayerbullet() - 1);
	}
}
