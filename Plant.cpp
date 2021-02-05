#include "stdafx.h"
#include "Plant.h"

HRESULT Plant::init(float x, float y)
{
	setAnimation();
	_pt.x = x;
	_pt.y = y;
	_currentWeapon = new pistol;
	_currentWeapon->init(_pt, NOWUSING);
	_width = 30;
	_height = 30;
	_speed = 5;
	_playerbullet = 30;
	_playerbulletMax = 150;
	_hp = 6;
	_maxhp = 8;
	_moveAngle = 0;
	_rc = RectMakeCenter(_pt.x, _pt.y, _width, _height);
	_direction = RIGHT;
	_playerstate = IDLE;
	_img = IMAGEMANAGER->findImage("plant_idle");
	_motion = plantidleright;
	_motion->start();
	_ishit = false;
	return S_OK;
}

void Plant::update()
{

	contral();
	_currentWeapon->update();
	_currentWeapon->setAngle(getAngle(_pt.x, _pt.y, CAMERAMANAGER->getMousePoint().x, CAMERAMANAGER->getMousePoint().y));
	_rc = RectMakeCenter(_pt.x, _pt.y, _width, _height);
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void Plant::render(HDC hdc)
{
	_img->aniRender(hdc, _pt.x - _img->getFrameWidth() / 2, _pt.y - _img->getFrameHeight() / 2, _motion);
	_currentWeapon->render(hdc);
}

void Plant::setAnimation()
{
	plantidleright = new animation;
	plantidleright->init("plant_idle");
	plantidleright->setPlayFrame(0, 3, false, true);
	plantidleright->setFPS(10);

	plantidlelft = new animation;
	plantidlelft->init("plant_idle");
	plantidlelft->setPlayFrame(7, 4, false, true);
	plantidlelft->setFPS(10);

	plantwalkright = new animation;
	plantwalkright->init("plant_walk");
	plantwalkright->setPlayFrame(0, 4, false, true);
	plantwalkright->setFPS(10);

	plantwalkleft = new animation;
	plantwalkleft->init("plant_walk");
	plantwalkleft->setPlayFrame(7, 4, false, true);
	plantwalkleft->setFPS(10);

	planthitright = new animation;
	planthitright->init("plant_hit");
	planthitright->setPlayFrame(0, 2, false, false, righthurt, this);
	planthitright->setFPS(10);

	planthitleft = new animation;
	planthitleft->init("plant_hit");
	planthitleft->setPlayFrame(3, 2, false, false, lefthurt, this);
	planthitleft->setFPS(10);

	plantdead = new animation;
	plantdead->init("plant_dead");
	plantdead->setPlayFrame(0, 3, false, false);//콜백필요
	plantdead->setFPS(10);

	plantmenuidle = new animation;
	plantmenuidle->init("plant_menuidle");
	plantmenuidle->setPlayFrame(0, 21, false, true);
	plantmenuidle->setFPS(10);
}

void Plant::contral()
{
	if (CAMERAMANAGER->getMousePoint().x < _pt.x)
	{
		_direction = LEFT;
	}
	else
	{
		_direction = RIGHT;
	}
	if (_playerstate == WALK)
	{
		if (!KEYMANAGER->isStayKeyDown('A') && !KEYMANAGER->isStayKeyDown('D') && !KEYMANAGER->isStayKeyDown('W') && !KEYMANAGER->isStayKeyDown('S'))
		{
			_playerstate = IDLE;

		}
	}
	if (KEYMANAGER->isOnceKeyDown('A') || KEYMANAGER->isOnceKeyDown('D') || KEYMANAGER->isOnceKeyDown('W') || KEYMANAGER->isOnceKeyDown('S'))
	{
		_playerstate = WALK;

	}


	if (_playerstate == IDLE && !_ishit)
	{
		if (_direction == LEFT)
		{
			_img = IMAGEMANAGER->findImage("plant_idle");
			_motion = plantidlelft;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
		else
		{
			_img = IMAGEMANAGER->findImage("plant_idle");
			_motion = plantidleright;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
	}

	if (_playerstate == WALK)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_pt.x -= 5;

		}
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_pt.x += 5;
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_pt.y -= 5;
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_pt.y += 5;
		}
		if (!_ishit)
		{
			if (_direction == LEFT)
			{
				_img = IMAGEMANAGER->findImage("plant_walk");
				_motion = plantwalkleft;
				if (!_motion->isPlay())
				{
					_motion->start();
				}
			}
			else
			{
				_img = IMAGEMANAGER->findImage("plant_walk");
				_motion = plantwalkright;
				if (!_motion->isPlay())
				{
					_motion->start();
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{

		_ishit = true;
	}
	if (_ishit)
	{
		if (_direction == LEFT)
		{
			_img = IMAGEMANAGER->findImage("plant_hit");
			_motion = planthitleft;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
		else
		{
			_img = IMAGEMANAGER->findImage("plant_hit");
			_motion = planthitright;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_playerstate = DEAD;
		_img = IMAGEMANAGER->findImage("plant_dead");
		_motion = plantdead;
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _playerbullet > 0)
	{
		_currentWeapon->fire();
		_playerbullet -= 1;
		if (_playerbullet < 0)
		{
			_playerbullet = 0;
		}
	}
}

void Plant::righthurt(void * obj)
{
	Plant*f = (Plant*)obj;
	f->setIshit(false);
	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_UP) && !KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		f->setState(IDLE);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_RIGHT) || KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		f->setState(WALK);
	}
}

void Plant::lefthurt(void * obj)
{
	Plant*f = (Plant*)obj;
	f->setIshit(false);
	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_UP) && !KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		f->setState(IDLE);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_RIGHT) || KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		f->setState(WALK);
	}
}

void Plant::makeDead(void * obj)
{
}
