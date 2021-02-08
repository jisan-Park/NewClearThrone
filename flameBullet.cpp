#include "stdafx.h"
#include "flameBullet.h"

HRESULT flameBullet::init()
{
	return S_OK;
}

void flameBullet::release()
{
}

void flameBullet::update()
{
	move();
	if (getDistance(_firept.x, _firept.y, _pt.x, _pt.y) > _range) _gone = true;
}

void flameBullet::render(HDC hdc)
{
	_img->frameRender(hdc, _rc.left, _rc.top, _count, 0);
}

void flameBullet::fire(POINT pt, float speed, float angle, int damage)
{
	_img = IMAGEMANAGER->findImage("salamander_bullet");
	_type = FLAME;
	_speed = speed;
	_count = 0;
	_cnt = 0;
	_damage = damage;
	_range = 1000;
	_radius = _img->getFrameWidth() / 2;
	_pt.x = _firept.x = pt.x;
	_pt.y = _firept.y = pt.y;
	_angle = angle;
}


void flameBullet::move()
{
	_cnt++;
	if (_cnt > 5)
	{
		_cnt = 0;
		if (_count < 6)
		{
			_count++;
			_speed-= 0.1f;
		}
		else _gone = true;
	}
	
	_pt.y += -sinf(_angle) * _speed;
	_pt.x += cosf(_angle) * _speed;
	_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());


}
