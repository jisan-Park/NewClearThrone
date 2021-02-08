﻿#include "stdafx.h"
#include "sword.h"

HRESULT sword::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("sword");
	_pt = pt;
	_radius = 20;
	_state = state;
	if (_state == NOWUSING) Position();
	else if (_state == ONGROUND)
	{
		_imgx = _pt.x;
		_imgy = _pt.y;
	}
	_type = SWORD;
	_damage = 10;
	_coolDown = 10;
	_coolCnt = _coolDown + PLAYERMANAGER->getPlayer()->getInterval();
	_angle = 0;

	return S_OK;
}

void sword::update()
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

void sword::fire()
{
	if (_coolCnt >= _coolDown + PLAYERMANAGER->getPlayer()->getInterval())
	{
		SOUNDMANAGER->play("칼", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
		playshortAngleEffect(_angle, _pt);
		POINT temppt;
		temppt = PointMake(_pt.x + cosf(_angle + _meleeAngle / 2) * _radius, _pt.y + -sinf(_angle + _meleeAngle / 2) * _radius);

		for (int i = 0; i < ENEMYMANAGER->getShowEnemyVector().size(); ++i)
		{
			ENEMYMANAGER->getShowEnemyVector()[i]->meleecollision(temppt, 30, _damage);
		}
		_coolCnt = 0;
		_meleeAngle *= (-1);
	}
}
