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
	_coolDown = 25;
	_coolCnt = _coolDown + PLAYERMANAGER->getPlayer()->getInterval();
	_angle = 0;
	_bulletSpd = 20;
	return S_OK;
}

void grenadeLauncher::update()
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

void grenadeLauncher::fire()
{
	if (_coolCnt >= _coolDown + PLAYERMANAGER->getPlayer()->getInterval() && PLAYERMANAGER->getPlayer()->getPlayerexplodeb() > 0)
	{
		SOUNDMANAGER->play("¾àÇÑÃÑ", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
		BULLETMANAGER->PlayerFire(GRENADE, _pt, _bulletSpd, _angle, _damage);
		PLAYERMANAGER->getPlayer()->setPlayerexplodeb(PLAYERMANAGER->getPlayer()->getPlayerexplodeb() - 1);
		_coolCnt = 0;
	}
}
