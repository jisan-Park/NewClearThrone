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
}

void bullet1::render(HDC hdc)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(hdc, _viBullet->rc.left, _viBullet->rc.top);
	}
}

void bullet1::fire(POINT pt, float speed, float angle, whoshot who)
{
	tagBullet bullet;
	bullet.who = who;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = IMAGEMANAGER->findImage("bullet1");
	bullet.speed = speed;
	bullet.radius = bullet.img->getWidth() / 2;
	bullet.pt.x = bullet.firept.x = pt.x;
	bullet.pt.y = bullet.firept.y = pt.y;
	bullet.angle = angle;
	bullet.rc = RectMakeCenter(bullet.pt.x, bullet.pt.y,
		bullet.img->getWidth(),
		bullet.img->getHeight());

	_vBullet.push_back(bullet);
}


void bullet1::setFrameIndex()
{
}

void bullet1::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->pt.x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->pt.y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->pt.x, _viBullet->pt.y,
			_viBullet->img->getWidth(),
			_viBullet->img->getHeight());
		++_viBullet;
	}
}
