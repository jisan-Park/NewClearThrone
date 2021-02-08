#include "stdafx.h"
#include "bbaRU.h"

HRESULT bbaRU::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("assassin_weapon");
	_pt = pt;
	_state = state;
	_type = BBARU;
	_radius = 20;
	_damage = 20;
	_coolDown = 0;
	_angle = 0;
	_bulletSpd = 0;
	setFrameIndex8(_angle);
	return S_OK;
}

void bbaRU::update()
{
	Position();
	setFrameIndex8(_angle);
}

void bbaRU::fire()
{
	POINT temppt;
	temppt = PointMake(_pt.x + cosf(_angle + _meleeAngle / 2) * _radius, _pt.y + -sinf(_angle + _meleeAngle / 2) * _radius);
	enemyMeleeAttack(temppt, 30, 5);
	_meleeAngle *= (-1);
}
