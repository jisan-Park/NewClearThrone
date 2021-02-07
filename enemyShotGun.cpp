#include "stdafx.h"
#include "enemyShotGun.h"

HRESULT enemyShotGun::init()
{
	return S_OK;
}

void enemyShotGun::release()
{
}

void enemyShotGun::update()
{
	if (getDistance(_firept.x, _firept.y, _pt.x, _pt.y) > _range) _gone = true;
	move();
}

void enemyShotGun::render(HDC hdc)
{
	_img->render(hdc, _rc.left, _rc.top);
}

void enemyShotGun::fire(POINT pt, float speed, float angle, int damage)
{
	_range = 200;
	_type = E_SHOTGUN;
	_img = IMAGEMANAGER->findImage("shotgun");
	_speed = speed;
	_damage = damage;
	_radius = _img->getFrameWidth() / 2;
	_pt.x = _firept.x = pt.x;
	_pt.y = _firept.y = pt.y;
	_angle = angle;
	_rc = RectMakeCenter(_pt.x, _pt.y,
		_img->getFrameWidth(),
		_img->getFrameHeight());
}

void enemyShotGun::setFrameIndex()
{
}

void enemyShotGun::move()
{
	if (_gone == true)
	{
		for (int i = 0; i < 4; i++)
		{
			BULLETMANAGER->EnemyFire(E_SHOTGUN2, _pt, _speed, _angle - 0.2f + 0.1f * i, 5);
		}
	}
	_pt.x += cosf(_angle) * _speed;
	_pt.y += -sinf(_angle) * _speed;
	_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());


}
