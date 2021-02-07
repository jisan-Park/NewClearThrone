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
}


void bullet::fire(POINT pt, float speed, float angle, int damage)
{
}

void bullet::setFrameIndex8()
{
	if ((_angle < PI8 * 1 && _angle >= 0) || (_angle > PI - PI8 && _angle < PI * 2)) _count = 0;
	if (_angle > PI8 * 1 && _angle <= PI8 * 3) _count = 1;
	if (_angle > PI8 * 3 && _angle <= PI8 * 5) _count = 2;
	if (_angle > PI8 * 5 && _angle <= PI8 * 7) _count = 3;
	if (_angle > PI8 * 7 && _angle <= PI8 * 9) _count = 4;
	if (_angle > PI8 * 9 && _angle <= PI8 * 11) _count = 5;
	if (_angle > PI8 * 11 && _angle <= PI8 * 13) _count = 6;
	if (_angle > PI8 * 13 && _angle <= PI8 * 15) _count = 7;
}


void bullet::move()
{

}

void bullet::explode()
{
}


