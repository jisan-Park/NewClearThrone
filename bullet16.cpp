#include "stdafx.h"
#include "bullet16.h"

HRESULT bullet16::init()
{

	return S_OK;
}

void bullet16::release()
{
}

void bullet16::update()
{
	move();

	if (getDistance(_firept.x, _firept.y, _pt.x, _pt.y) > _range) _gone = true;
}

void bullet16::render(HDC hdc)
{
	_img->frameRender(hdc, _rc.left, _rc.top, _count, 0);
}

void bullet16::fire(POINT pt, float speed, float angle, int damage)
{
	_img = IMAGEMANAGER->findImage("bullet16");
	_type = ANGLE16;
	_speed = speed;
	_damage = damage;
	_range = 2000;
	_radius = _img->getFrameWidth() / 2;
	_pt.x = _firept.x = pt.x;
	_pt.y = _firept.y = pt.y;
	_angle = angle;
	if (_angle >= PI2) _angle -= PI2;
	if (_angle <= 0) _angle += PI2;
	if ((_angle < PI16 * 1 && _angle >= 0) || (_angle > PI - PI16 && _angle < PI * 2)) _count = 0;
	if (_angle > PI16 * 1 && _angle <= PI16 * 3) _count = 1;
	if (_angle > PI16 * 3 && _angle <= PI16 * 5) _count = 2;
	if (_angle > PI16 * 5 && _angle <= PI16 * 7) _count = 3;
	if (_angle > PI16 * 7 && _angle <= PI16 * 9) _count = 4;
	if (_angle > PI16 * 9 && _angle <= PI16 * 11) _count = 5;
	if (_angle > PI16 * 11 && _angle <= PI16 * 13) _count = 6;
	if (_angle > PI16 * 13 && _angle <= PI16 * 15) _count = 7;
	if (_angle > PI16 * 15 && _angle <= PI16 * 17) _count = 8;
	if (_angle > PI16 * 17 && _angle <= PI16 * 19) _count = 9;
	if (_angle > PI16 * 19 && _angle <= PI16 * 21) _count = 10;
	if (_angle > PI16 * 21 && _angle <= PI16 * 23) _count = 11;
	if (_angle > PI16 * 23 && _angle <= PI16 * 25) _count = 12;
	if (_angle > PI16 * 25 && _angle <= PI16 * 27) _count = 13;
	if (_angle > PI16 * 27 && _angle <= PI16 * 29) _count = 14;
	if (_angle > PI16 * 29 && _angle <= PI16 * 31) _count = 15;

	_rc = RectMakeCenter(_pt.x, _pt.y,
		_img->getFrameWidth(),
		_img->getFrameHeight());
}

void bullet16::setFrameIndex()
{
}

void bullet16::move()
{
	_pt.y += -sinf(_angle) * _speed;
	_pt.x += cosf(_angle) * _speed;
	_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
}
