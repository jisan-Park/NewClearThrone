#include "stdafx.h"
#include "enemyShotGun2.h"

HRESULT enemyShotGun2::init()
{
	return S_OK;
}

void enemyShotGun2::release()
{
}

void enemyShotGun2::update()
{
	move();

	if (getDistance(_firept.x, _firept.y, _pt.x, _pt.y) > _range) _gone = true;
}

void enemyShotGun2::render(HDC hdc)
{
	_img->render(hdc, _rc.left, _rc.top);
}

void enemyShotGun2::fire(POINT pt, float speed, float angle, int damage)
{
	_range = 2000;
	_type = E_ANGLE16_2;
	_img = IMAGEMANAGER->findImage("shotgun2");
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

void enemyShotGun2::setFrameIndex()
{
}

void enemyShotGun2::move()
{
	_pt.x += cosf(_angle) * _speed;
	_pt.y += -sinf(_angle) * _speed;

	_rc = RectMakeCenter(_pt.x, _pt.y,
		_img->getWidth(),
		_img->getHeight());
}
