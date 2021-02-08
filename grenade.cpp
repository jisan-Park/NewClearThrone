#include "stdafx.h"
#include "grenade.h"

HRESULT grenade::init()
{
	return S_OK;
}

void grenade::release()
{
}

void grenade::update()
{
	move();
}

void grenade::render(HDC hdc)
{
	_img->frameRender(hdc, _rc.left, _rc.top, _count, 0);
}

void grenade::fire(POINT pt, float speed, float angle, int damage)
{
	_img = IMAGEMANAGER->findImage("¼ö·ùÅº");
	_speed = speed;
	_damage = damage;
	_type = GRENADE;
	_radius = _img->getFrameWidth() / 2;
	_pt.x = _firept.x = pt.x;
	_pt.y = _firept.y = pt.y;
	_angle = angle;
	setFrameIndex8();
	_rc = RectMakeCenter(_pt.x, _pt.y,
		_img->getFrameWidth(),
		_img->getFrameHeight());
}

void grenade::setFrameIndex()
{
}

void grenade::explode()
{
	for (int i = 0; i < ENEMYMANAGER->getShowEnemyVector().size(); ++i)
	{
		ENEMYMANAGER->getShowEnemyVector()[i]->explosion(_pt, 200, 20);
	}
}

void grenade::move()
{


	if (_speed > 0.5f) _speed -= 0.5f;
	if (_speed <= 0.5f) _cnt++;
	if (_cnt > 20) _gone = true;
	if (_gone == true)
	{
		explode();
	}

	_pt.x += cosf(_angle) * _speed;
	_pt.y += -sinf(_angle) * _speed;
	_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
}
