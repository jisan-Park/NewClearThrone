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
	if(!_isFire&&_img != NULL)
	{ 
		_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
		_rc = RectMakeCenter(_pt.x, _pt.y, 80, 60);
		for (int i = 0; i < ENEMYMANAGER->getShowEnemyVector().size(); ++i)
		{
			ENEMYMANAGER->getShowEnemyVector()[i]->plantSkill(_rc);
		}
	}
	if (_isFire) ENEMYMANAGER->plantSkill();

}

void plantbullet::render(HDC hdc)
{
	if (_img != NULL)
	{
		if (!_isFire)
		{
			_img->aniRender(hdc, _rc.left, _rc.top, _motion);
		}
		else
		{
			_img->render(hdc, _rc.left, _rc.top);
		}
	}
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
	RECT temp;
	
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
			_speed = 0;

		}
	}
	//if (!_isFire)
	//{
	//	_img = IMAGEMANAGER->findImage("plant_skill");
	//	_motion = _plantbullet;
	//
	//	if (_motion->isPlay() == false) _motion->start();
	//	_speed = 0;
	//}
	
	
}

void plantbullet::setAni()
{
	_plantbullet = new animation;
	_plantbullet->init("plant_skill");
	_plantbullet->setPlayFrame(0, 4, false, false);
	_plantbullet->setFPS(10);
}

void plantbullet::collision()
{
	//if (_isFire != _isFire && _img != NULL)
	//{
	//	for (int i = 0; i < ENEMYMANAGER->getShowEnemyVector().size(); ++i)
	//	{
	//		RECT temp;
	//		if (IntersectRect(&temp, &ENEMYMANAGER->getShowEnemyVector()[i]->getInfo().rc, &_rc)
	//	}
	//}
}

void plantbullet::setMotion()
{
	_motion = _plantbullet;
	_speed = 0;
	if (!_motion->isPlay())
	{
		_motion->start();
	}
}
