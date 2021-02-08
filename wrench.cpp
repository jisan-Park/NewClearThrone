#include "stdafx.h"
#include "wrench.h"

HRESULT wrench::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("wrench");
	_pt = pt;
	_radius = 20;
	_state = state;
	if (_state == NOWUSING) Position();
	else if (_state == ONGROUND)
	{
		_imgx = _pt.x;
		_imgy = _pt.y;
	}
	_type = WRENCH;
	_damage = 5;
	_coolDown = 5;
	_coolCnt = _coolDown + PLAYERMANAGER->getPlayer()->getInterval();
	_angle = 0;
	_bulletSpd = 1;

	return S_OK;
}

void wrench::update()
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

void wrench::fire()
{
	if (_coolCnt >= _coolDown + PLAYERMANAGER->getPlayer()->getInterval())
	{
		POINT temppt;
		temppt = PointMake(_pt.x + cosf(_angle + _meleeAngle / 2) * _radius, _pt.y + -sinf(_angle + _meleeAngle / 2) * _radius);
		for (int i = 0; i < ENEMYMANAGER->getShowEnemyVector().size(); ++i)
		{
			ENEMYMANAGER->getShowEnemyVector()[i]->meleecollision(temppt, 20, _damage);
		}
		_meleeAngle *= (-1);
		_coolCnt = 0;
	}
}
