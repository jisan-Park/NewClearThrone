#include "stdafx.h"
#include "shovel.h"


HRESULT shovel::init(POINT pt, weaponState state)
{
	_img = IMAGEMANAGER->findImage("shovel");
	_pt = pt;
	_radius = 20;
	_state = state;
	if (_state == NOWUSING) Position();
	else if (_state == ONGROUND)
	{
		_imgx = _pt.x;
		_imgy = _pt.y;
	}
	_type = SHOVEL;
	_radius = 20;
	_damage = 20;
	_coolDown = 25;
	_coolCnt = _coolDown + PLAYERMANAGER->getPlayer()->getInterval();
	_bulletSpd = 1;
	_angle = 0;
	return S_OK;
}

void shovel::render(HDC hdc)
{
	_img->frameRender(hdc, _imgx - _img->getFrameWidth() / 2, _imgy - _img->getFrameHeight() / 2, _index, 0);
}

void shovel::update()
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

void shovel::fire()
{
	if (_coolCnt >= _coolDown + PLAYERMANAGER->getPlayer()->getInterval())
	{
		_meleeAngle *= (-1);
		_coolCnt = 0;
	}
}
