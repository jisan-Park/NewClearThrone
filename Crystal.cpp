#include "stdafx.h"
#include "Crystal.h"

HRESULT Crystal::init(float x, float y)
{
	setAnimation();
	_pt.x = x;
	_pt.y = y;
	_currentWeapon = new pistol;
	_currentWeapon->init(_pt, NOWUSING);
	_width = 30;
	_height = 30;
	_speed = 5;
	_playerbullet = 150;
	_playerbulletMax = 150;
	_playershellb = 100;
	_playershellbMax = 150;
	_playerenergyb = 100;
	_playerenergubMax = 100;
	_playerexplodeb = 100;
	_playerecplodbeMax = 100;
	_hp = 8;
	_maxhp = 8;
	_moveAngle = 0;
	_rc = RectMakeCenter(_pt.x, _pt.y, _width, _height);
	_direction = RIGHT;
	_playerstate = IDLE;
	_img = IMAGEMANAGER->findImage("crystal_idle");
	_motion = crystalidleright;
	_motion->start();
	_ishit = false;
	return S_OK;
}

void Crystal::update()
{
	pybullet();
	MAPMANAGER->collision(_rc);
	if (_hp > _maxhp)
	{
		_hp = _maxhp;
	}
	contral();
	collision();
	_rc = RectMakeCenter(_pt.x, _pt.y, _width, _height);
	_currentWeapon->update();
	_currentWeapon->setAngle(getAngle(_pt.x, _pt.y, CAMERAMANAGER->getMousePoint().x, CAMERAMANAGER->getMousePoint().y));
	if (_weaponReady == true)
	{
		_readyWeapon->update();
		_readyWeapon->setAngle(0);
	}


	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
	
}

void Crystal::render(HDC hdc)
{
	if (_playerstate == SKILL)
	{
		//_img->aniRender(hdc, _pt.x - 6, _pt.y - 20, _motion);
		_img->aniRender(hdc, _pt.x - _img->getFrameWidth() / 2, _pt.y - _img->getFrameHeight() / 2, _motion);
	}
	else
	{
		//_img->aniRender(hdc, _pt.x, _pt.y, _motion);
		_img->aniRender(hdc, _pt.x - _img->getFrameWidth() / 2, _pt.y - _img->getFrameHeight() / 2, _motion);
	}
	_currentWeapon->render(hdc);
}

void Crystal::setAnimation()
{
	crystalidleright = new animation;
	crystalidleright->init("crystal_idle");
	crystalidleright->setPlayFrame(0, 3, false, true);
	crystalidleright->setFPS(10);

	crystalidleleft = new animation;
	crystalidleleft->init("crystal_idle");
	crystalidleleft->setPlayFrame(7, 4, false, true);
	crystalidleleft->setFPS(10);

	crystalwalkright = new animation;
	crystalwalkright->init("crystal_walk");
	crystalwalkright->setPlayFrame(0, 5, false, true);
	crystalwalkright->setFPS(10);

	crystalwalkleft = new animation;
	crystalwalkleft->init("crystal_walk");
	crystalwalkleft->setPlayFrame(11, 6, false, true);
	crystalwalkleft->setFPS(10);

	crystalhitright = new animation;
	crystalhitright->init("crystal_hit");
	crystalhitright->setPlayFrame(0, 2, false, false, righthurt, this);
	crystalhitright->setFPS(10);

	crystalhitleft = new animation;
	crystalhitleft->init("crystal_hit");
	crystalhitleft->setPlayFrame(3, 2, false, false, lefthurt, this);
	crystalhitleft->setFPS(10);

	crystalskill = new animation;
	crystalskill->init("crystal_skill");
	crystalskill->setPlayFrame(0, 5, false, false, skillback, this);
	crystalskill->setFPS(6);

	crystaldead = new animation;
	crystaldead->init("crystal_dead");
	crystaldead->setPlayFrame(0, 3, false, false);//콜백필요
	crystaldead->setFPS(10);

	
}

void Crystal::contral()
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
			_img = IMAGEMANAGER->findImage("crystal_idle");
			_motion = crystalidleleft;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
		else
		{
			_img = IMAGEMANAGER->findImage("crystal_idle");
			_motion = crystalidleright;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
	}

	if (_playerstate == WALK)
	{
		if (!MAPMANAGER->isCollisionTile(_pt,_width,_height)) {
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
		}
		
		if (!_ishit)
		{
			if (_direction == LEFT)
			{
				_img = IMAGEMANAGER->findImage("crystal_walk");
				_motion = crystalwalkleft;
				if (!_motion->isPlay())
				{
					_motion->start();
				}
			}
			else
			{
				_img = IMAGEMANAGER->findImage("crystal_walk");
				_motion = crystalwalkright;
				if (!_motion->isPlay())
				{
					_motion->start();
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{

		if (_weaponReady) playerWeaponSwap();
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (_weaponReady == true) ITEMMANAGER->weaponSwap();
		if (_weaponReady == false) ITEMMANAGER->grabWeapon();
	}
	if (_ishit)
	{
		if (_direction == LEFT)
		{
			_img = IMAGEMANAGER->findImage("crystal_hit");
			_motion = crystalhitleft;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
		else
		{
			_img = IMAGEMANAGER->findImage("crystal_hit");
			_motion = crystalhitright;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
	}
	
	if (_hp <= 0 && !_isStrongSpirit)
	{
		_playerstate = DEAD;
		_img = IMAGEMANAGER->findImage("crystal_dead");
		_motion = crystaldead;
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_isStrongSpirit&&_hp <= 0)
	{
		_count++;
		if (_count < 300)
		{
			_hp = 1;
		}
		else
		{
			_count = 0;
			_isStrongSpirit = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_playerstate = SKILL;
		_img = IMAGEMANAGER->findImage("crystal_skill");
		_motion = crystalskill;
		if (!_motion->isPlay())
		{
			_motion->start();
		}

	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		switch (_currentWeapon->getType())
		{
		case ASSULTRIFLE:	case GRENADELAUNCHER:		case PISTOL:	case RAZERRIFLE:	case SHOTGUN:	case SHOVEL:	case SWORD:		case WRENCH:
			_currentWeapon->fire();
			break;
		default:
			break;
		}

	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		switch (_currentWeapon->getType())
		{
		case MACHINEGUN:	case TRIPLEMACHINEGUN:
			_currentWeapon->fire();
			break;
		default:
			break;
		}
	}
}

void Crystal::righthurt(void * obj)
{
	Crystal*f = (Crystal*)obj;
	f->setIshit(false);
	
}

void Crystal::lefthurt(void * obj)
{
	Crystal*f = (Crystal*)obj;
	f->setIshit(false);
	
}

void Crystal::skillback(void * obj)
{
	Crystal*f = (Crystal*)obj;
	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_UP) && !KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		f->setState(IDLE);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_RIGHT) || KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		f->setState(WALK);

	}
}

void Crystal::makeDead(void * obj)
{
}
