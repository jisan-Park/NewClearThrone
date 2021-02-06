#include "stdafx.h"
#include "bullet1.h"

HRESULT bullet1::init()
{
	_range = 2000;
	return S_OK;
}

void bullet1::release()
{
}

void bullet1::update()
{
	move();
	if (getDistance(_firept.x, _firept.y, _pt.x, _pt.y) > _range) _gone = true;
}

void bullet1::render(HDC hdc)
{
	_img->render(hdc, _rc.left, _rc.top);
}

void bullet1::fire(POINT pt, float speed, float angle, int damage)
{
	_range = 2000;
	_img = IMAGEMANAGER->findImage("bullet1");
	_speed = speed;
	_radius = _img->getWidth() / 2;
	_damage = damage;
	_pt.x = _firept.x = pt.x;
	_pt.y = _firept.y = pt.y;
	_angle = angle;
	_rc = RectMakeCenter(_pt.x, _pt.y,
		_img->getWidth(),
		_img->getHeight());
}


void bullet1::setFrameIndex()
{
}

void bullet1::move()
{
	_pt.x += cosf(_angle) * _speed;
	_pt.y += -sinf(_angle) * _speed;

	_rc = RectMakeCenter(_pt.x, _pt.y,
		_img->getWidth(),
		_img->getHeight());
}
