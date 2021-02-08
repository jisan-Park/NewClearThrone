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
	_img = IMAGEMANAGER->findImage("eyes_idle");
	_img2 = IMAGEMANAGER->findImage("eyes_skill");
	_motion2 = eyesskill;
	_motion = eyesidleright;
	_motion->start();
	_ishit = false;
	return S_OK;
}

void Eyes::update()
{

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

void Eyes::render(HDC hdc)
{
	_img->aniRender(hdc, _pt.x - _img->getFrameWidth() / 2, _pt.y - _img->getFrameHeight() / 2, _motion);
	_currentWeapon->render(hdc);
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		_img2->aniRender(hdc, _pt.x - _img2->getFrameWidth() / 2, _pt.y - _img2->getFrameHeight()-20, _motion2);
	}
	
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


	eyesskill = new animation;
	eyesskill->init("eyes_skill");
	eyesskill->setPlayFrame(0, 2, false, false);
	eyesskill->setFPS(10);

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
		if (!MAPMANAGER->isCollisionTile(_pt, _width, _height)) {
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
	if (_hp <= 0 && !_isStrongSpirit)
	{
		_playerstate = DEAD;
		_img = IMAGEMANAGER->findImage("eyes_dead");
		_motion = eyesdead;
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
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < ENEMYMANAGER->getShowEnemyVector().size(); ++i)
		{
			ENEMYMANAGER->getShowEnemyVector()[i]->eyeSkill(_pt.x, _pt.y);
		}
		_img2 = IMAGEMANAGER->findImage("eyes_skill");
		_motion2 = eyesskill;
		if (!_motion2->isPlay())
		{
			_motion2->start();
		}
		_motion2->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
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

void Eyes::righthurt(void * obj)
{
	Eyes*f = (Eyes*)obj;
	f->setIshit(false);

}

void Eyes::lefthurt(void * obj)
{
	Eyes*f = (Eyes*)obj;
	f->setIshit(false);
	
}

void Eyes::makeDead(void * obj)
{
}
