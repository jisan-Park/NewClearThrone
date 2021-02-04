#include "stdafx.h"
#include "bullet16.h"

HRESULT bullet16::init()
{
	_range = 2000;
	return S_OK;
}

void bullet16::release()
{
}

void bullet16::update()
{
	move();
}

void bullet16::render(HDC hdc)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(hdc, _viBullet->rc.left, _viBullet->rc.top, _viBullet->count, 0);
		//Rectangle(hdc, _viBullet->rc);
	}
}

void bullet16::fire(POINT pt, float speed, float angle, whoshot who)
{
	tagBullet bullet;
	bullet.who = who;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = IMAGEMANAGER->findImage("bullet16");
	bullet.speed = speed;
	bullet.radius = bullet.img->getFrameWidth() / 2;
	bullet.pt.x = bullet.firept.x = pt.x;
	bullet.pt.y = bullet.firept.y = pt.y;
	bullet.angle = angle;
	if (bullet.angle >= PI2) bullet.angle -= PI2;
	if (bullet.angle <= 0) bullet.angle += PI2;
	if ((bullet.angle < PI16 * 1 && bullet.angle >= 0) || (bullet.angle > PI - PI16 && bullet.angle < PI * 2)) bullet.count = 0;
	if (bullet.angle > PI16 * 1 && bullet.angle <= PI16 * 3) bullet.count = 1;
	if (bullet.angle > PI16 * 3 && bullet.angle <= PI16 * 5) bullet.count = 2;
	if (bullet.angle > PI16 * 5 && bullet.angle <= PI16 * 7) bullet.count = 3;
	if (bullet.angle > PI16 * 7 && bullet.angle <= PI16 * 9) bullet.count = 4;
	if (bullet.angle > PI16 * 9 && bullet.angle <= PI16 * 11) bullet.count = 5;
	if (bullet.angle > PI16 * 11 && bullet.angle <= PI16 * 13) bullet.count = 6;
	if (bullet.angle > PI16 * 13 && bullet.angle <= PI16 * 15) bullet.count = 7;
	if (bullet.angle > PI16 * 15 && bullet.angle <= PI16 * 17) bullet.count = 8;
	if (bullet.angle > PI16 * 17 && bullet.angle <= PI16 * 19) bullet.count = 9;
	if (bullet.angle > PI16 * 19 && bullet.angle <= PI16 * 21) bullet.count = 10;
	if (bullet.angle > PI16 * 21 && bullet.angle <= PI16 * 23) bullet.count = 11;
	if (bullet.angle > PI16 * 23 && bullet.angle <= PI16 * 25) bullet.count = 12;
	if (bullet.angle > PI16 * 25 && bullet.angle <= PI16 * 27) bullet.count = 13;
	if (bullet.angle > PI16 * 27 && bullet.angle <= PI16 * 29) bullet.count = 14;
	if (bullet.angle > PI16 * 29 && bullet.angle <= PI16 * 31) bullet.count = 15;

	bullet.rc = RectMakeCenter(bullet.pt.x, bullet.pt.y,
		bullet.img->getFrameWidth(),
		bullet.img->getFrameHeight());

	_vBullet.push_back(bullet);
}

void bullet16::setFrameIndex()
{
}

void bullet16::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->pt.x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->pt.y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->pt.x, _viBullet->pt.y,
			_viBullet->img->getFrameWidth(),
			_viBullet->img->getFrameHeight());

		//if (_range < getDistance(_viBullet->pt.x, _viBullet->pt.y, _viBullet->firept.x, _viBullet->firept.y))
		//{
		//	_viBullet = _vBullet.erase(_viBullet);
		//}
		++_viBullet;
	}

}
