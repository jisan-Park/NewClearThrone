#include "stdafx.h"
#include "plantbullet.h"

HRESULT plantbullet::init()
{
	_range = 300;
	setAni();

	return S_OK;
}

void plantbullet::release()
{

}

void plantbullet::update()
{
	move();
	if (_range < getDistance(_pt.x, _pt.y, _firept.x, _firept.y))
	{
		_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
		_rc = RectMakeCenter(_pt.x, _pt.y, 80, 60);
	}

}

void plantbullet::render(HDC hdc)
{
	if (_isFire)
	{
		_img->render(hdc, _rc.left, _rc.top);
	}
	if (_range < getDistance(_pt.x, _pt.y, _firept.x, _firept.y))
	{
		_img->aniRender(hdc, _rc.left, _rc.top, _motion);
	}
	Rectangle(hdc, _rc);
}

void plantbullet::fire(POINT pt, float speed, float angle)
{



	_img = IMAGEMANAGER->findImage("plant_bullet");
	_speed = speed;
	_isFire = true;
	_pt.x = _firept.x = pt.x;
	_pt.y = _firept.y = pt.y;
	_angle = angle;
	_rc = RectMakeCenter(_pt.x, _pt.y, 20, 20);

}

void plantbullet::move()
{
	_pt.x += cosf(_angle) * _speed;
	_pt.y += -sinf(_angle) * _speed;

	_rc = RectMakeCenter(_pt.x, _pt.y, 20, 20);
	if (_range < getDistance(_pt.x, _pt.y, _firept.x, _firept.y) && _isFire)
	{
		_isFire = false;
		if (!_isFire)
		{
			_img = IMAGEMANAGER->findImage("plant_skill");
			_motion = _plantbullet;
			if (!_motion->isPlay())
			{
				_motion->start();
			}

		}
		_speed = 0;
	}
}

void plantbullet::setAni()
{
	_plantbullet = new animation;
	_plantbullet->init("plant_skill");
	_plantbullet->setPlayFrame(0, 4, false, false);
	_plantbullet->setFPS(10);
}
