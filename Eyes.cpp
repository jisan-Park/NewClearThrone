#include "stdafx.h"
#include "Eyes.h"

HRESULT Eyes::init(float x, float y)
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
	_img = IMAGEMANAGER->findImage("eyes_idle");
	_motion = eyesidleright;
	_motion->start();
	_ishit = false;
	return S_OK;
}

void Eyes::update()
{

	contral();
	_currentWeapon->update();
	_currentWeapon->setAngle(getAngle(_pt.x, _pt.y, CAMERAMANAGER->getMousePoint().x, CAMERAMANAGER->getMousePoint().y));
	_rc = RectMakeCenter(_pt.x, _pt.y, _width, _height);
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void Eyes::render(HDC hdc)
{
	_img->aniRender(hdc, _pt.x - _img->getFrameWidth() / 2, _pt.y - _img->getFrameHeight() / 2, _motion);
	_currentWeapon->render(hdc);
}

void Eyes::setAnimation()
{
	eyesidleright = new animation;
	eyesidleright->init("eyes_idle");
	eyesidleright->setPlayFrame(0, 3, false, true);
	eyesidleright->setFPS(10);

	eyesidleleft = new animation;
	eyesidleleft->init("eyes_idle");
	eyesidleleft->setPlayFrame(7, 4, false, true);
	eyesidleleft->setFPS(10);

	eyeswalkright = new animation;
	eyeswalkright->init("eyes_walk");
	eyeswalkright->setPlayFrame(0, 5, false, true);
	eyeswalkright->setFPS(10);

	eyeswalkleft = new animation;
	eyeswalkleft->init("eyes_walk");
	eyeswalkleft->setPlayFrame(11, 6, false, true);
	eyeswalkleft->setFPS(10);

	eyeshitright = new animation;
	eyeshitright->init("eyes_hit");
	eyeshitright->setPlayFrame(0, 2, false, false, righthurt, this);
	eyeshitright->setFPS(10);

	eyeshitleft = new animation;
	eyeshitleft->init("eyes_hit");
	eyeshitleft->setPlayFrame(3, 2, false, false, lefthurt, this);
	eyeshitleft->setFPS(10);

	eyesdead = new animation;
	eyesdead->init("eyes_dead");
	eyesdead->setPlayFrame(0, 3, false, false);//콜백필요
	eyesdead->setFPS(6);

	//eyesmenuidle = new animation;
	//eyesmenuidle->init("eyes_menuidle");
	//eyesmenuidle->setPlayFrame(0, 23, false, true);
	//eyesmenuidle->setFPS(10);

}

void Eyes::contral()
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
			_img = IMAGEMANAGER->findImage("eyes_idle");
			_motion = eyesidleleft;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
		else
		{
			_img = IMAGEMANAGER->findImage("eyes_idle");
			_motion = eyesidleright;
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
				_img = IMAGEMANAGER->findImage("eyes_walk");
				_motion = eyeswalkleft;
				if (!_motion->isPlay())
				{
					_motion->start();
				}
			}
			else
			{
				_img = IMAGEMANAGER->findImage("eyes_walk");
				_motion = eyeswalkright;
				if (!_motion->isPlay())
				{
					_motion->start();
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//_ishit = true;
		playerWeaponSwap();
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		ITEMMANAGER->weaponSwap();
	}
	if (_ishit)
	{
		if (_direction == LEFT)
		{
			_img = IMAGEMANAGER->findImage("eyes_hit");
			_motion = eyeshitleft;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
		else
		{
			_img = IMAGEMANAGER->findImage("eyes_hit");
			_motion = eyeshitright;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_playerstate = DEAD;
		_img = IMAGEMANAGER->findImage("eyes_dead");
		_motion = eyesdead;
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

void Eyes::righthurt(void * obj)
{
	Eyes*f = (Eyes*)obj;
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

void Eyes::lefthurt(void * obj)
{
	Eyes*f = (Eyes*)obj;
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

void Eyes::makeDead(void * obj)
{
}
