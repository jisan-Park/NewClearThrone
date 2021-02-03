#include "stdafx.h"
#include "bullet.h"

HRESULT bullet::init()
{
	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	move();
}

void bullet::render(HDC hdc)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(hdc,
			_viBullet->rc.left,
			_viBullet->rc.top,
			_viBullet->img->getFrameX(), 0);

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}

			_viBullet->count = 0;
		}
	}
}

void bullet::removeBullet(int arrnum)
{
	_vBullet.erase(_vBullet.begin() + arrnum);
}

void bullet::fire(POINT pt, float speed, float angle, whoshot who)
{
}

void bullet::fire(POINT pt, float speed, float angle, float turnangle, whoshot who)
{
}

void bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->pt.y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->pt.x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pt.x, _viBullet->pt.y,
			_viBullet->img->getFrameWidth(),
			_viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->pt.x, _viBullet->pt.y,
			_viBullet->firept.x, _viBullet->firept.y))
		{
			SAFE_RELEASE(_viBullet->img);
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}


