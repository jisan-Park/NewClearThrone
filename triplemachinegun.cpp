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
	_coolDown = 5;
	_coolCnt = _coolDown + PLAYERMANAGER->getPlayer()->getInterval();
	_bulletSpd = 15;
	_angle = 0;

	return S_OK;
}

void triplemachinegun::update()
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

void triplemachinegun::fire()
{
	if (_coolCnt >= _coolDown + PLAYERMANAGER->getPlayer()->getInterval() && PLAYERMANAGER->getPlayer()->getPlayerbullet() > 0)
	{
		SOUNDMANAGER->play("´Ü¹ß", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
		for (int i = 0; i < 3; i++)
		{
			if (PLAYERMANAGER->getPlayer()->getPlayerbullet() <= 0) break;
			BULLETMANAGER->PlayerFire(ANGLE16, _pt, _bulletSpd, _angle - (0.05f - 0.01f * PLAYERMANAGER->getPlayer()->getAngleCard())+ (0.05f - 0.01f * PLAYERMANAGER->getPlayer()->getAngleCard())* i, _damage);
			PLAYERMANAGER->getPlayer()->setPlayerbullet(PLAYERMANAGER->getPlayer()->getPlayerbullet() - 1);
		}
		_coolCnt = 0;
	}
}
