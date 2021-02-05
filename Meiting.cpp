#include "stdafx.h"
#include "Meiting.h"

HRESULT Meiting::init(float x, float y)
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
	_img = IMAGEMANAGER->findImage("melting_idle");
	_motion = meltingidleright;
	_motion->start();
	_ishit = false;
	return S_OK;
}

void Meiting::update()
{

	contral();
	_currentWeapon->update();
	_currentWeapon->setAngle(getAngle(_pt.x, _pt.y, CAMERAMANAGER->getMousePoint().x, CAMERAMANAGER->getMousePoint().y));
	_rc = RectMakeCenter(_pt.x, _pt.y, _width, _height);
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void Meiting::render(HDC hdc)
{
	_img->aniRender(hdc, _pt.x - _img->getFrameWidth() / 2, _pt.y - _img->getFrameHeight() / 2, _motion);
	_currentWeapon->render(hdc);
}

void Meiting::setAnimation()
{
	meltingidleright = new animation;
	meltingidleright->init("melting_idle");
	meltingidleright->setPlayFrame(0, 3, false, true);
	meltingidleright->setFPS(10);

	meltingidleleft = new animation;
	meltingidleleft->init("melting_idle");
	meltingidleleft->setPlayFrame(7, 4, false, true);
	meltingidleleft->setFPS(10);

	meltingwalkright = new animation;
	meltingwalkright->init("melting_walk");
	meltingwalkright->setPlayFrame(0, 5, false, true);
	meltingwalkright->setFPS(10);

	meltingwalkleft = new animation;
	meltingwalkleft->init("melting_walk");
	meltingwalkleft->setPlayFrame(11, 6, false, true);
	meltingwalkleft->setFPS(10);

	meltinghitright = new animation;
	meltinghitright->init("melting_hit");
	meltinghitright->setPlayFrame(0, 2, false, false, righthurt, this);
	meltinghitright->setFPS(10);

	meltinghitleft = new animation;
	meltinghitleft->init("melting_hit");
	meltinghitleft->setPlayFrame(3, 2, false, false, lefthurt, this);
	meltinghitleft->setFPS(10);

	meltingdead = new animation;
	meltingdead->init("melting_dead");
	meltingdead->setPlayFrame(0, 3, false, false);//콜백필요
	meltingdead->setFPS(10);

	meltingmenuidle = new animation;
	meltingmenuidle->init("melting_menuidle");
	meltingmenuidle->setPlayFrame(0, 16, false, true);
	meltingmenuidle->setFPS(10);
}

void Meiting::contral()
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
			_img = IMAGEMANAGER->findImage("melting_idle");
			_motion = meltingidleleft;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
		else
		{
			_img = IMAGEMANAGER->findImage("melting_idle");
			_motion = meltingidleright;
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
				_img = IMAGEMANAGER->findImage("melting_walk");
				_motion = meltingwalkleft;
				if (!_motion->isPlay())
				{
					_motion->start();
				}
			}
			else
			{
				_img = IMAGEMANAGER->findImage("melting_walk");
				_motion = meltingwalkright;
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
			_img = IMAGEMANAGER->findImage("melting_hit");
			_motion = meltinghitleft;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
		else
		{
			_img = IMAGEMANAGER->findImage("melting_hit");
			_motion = meltinghitright;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_playerstate = DEAD;
		_img = IMAGEMANAGER->findImage("melting_dead");
		_motion = meltingdead;
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

void Meiting::righthurt(void * obj)
{
	Meiting*f = (Meiting*)obj;
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

void Meiting::lefthurt(void * obj)
{
	Meiting*f = (Meiting*)obj;
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

void Meiting::makeDead(void * obj)
{
}
