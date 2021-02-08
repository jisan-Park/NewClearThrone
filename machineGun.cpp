#include "stdafx.h"
#include "machineGun.h"

HRESULT machineGun::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("machinegun");
	_pt = pt;
	_radius = 20;
	_state = state;
	if (_state == NOWUSING) Position();
	else if (_state == ONGROUND)
	{
		_imgx = _pt.x;
		_imgy = _pt.y;
	}
	_type = MACHINEGUN;
	_damage = 5;
	_bulletSpd = 15;
	_coolDown = 3;
	_coolCnt = _coolDown + PLAYERMANAGER->getPlayer()->getInterval();
	_angle = 0;

	return S_OK;
}

void machineGun::update()
{
	setFrameIndex(_angle);
	if (_coolCnt <= _coolDown + PLAYERMANAGER->getPlayer()->getInterval()) _coolCnt++;
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

void machineGun::fire()
{
	if (_coolCnt >= _coolDown + PLAYERMANAGER->getPlayer()->getInterval() && PLAYERMANAGER->getPlayer()->getPlayerbullet() > 0)
	{
		SOUNDMANAGER->play("¾àÇÑÃÑ", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
		BULLETMANAGER->PlayerFire(ANGLE16, _pt, _bulletSpd, _angle + RND->getFromFloatTo(-(_rndSpreadAngle - 0.01 * PLAYERMANAGER->getPlayer()->getAngleCard()), (_rndSpreadAngle - 0.01 * PLAYERMANAGER->getPlayer()->getAngleCard())), _damage);
		PLAYERMANAGER->getPlayer()->setPlayerbullet(PLAYERMANAGER->getPlayer()->getPlayerbullet() - 1);
		_coolCnt = 0;
	}
}
