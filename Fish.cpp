#include "stdafx.h"
#include "Fish.h"

HRESULT Fish::init(float x, float y)
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
	_img = IMAGEMANAGER->findImage("fish_idle");
	_motion = fishidleright;
	_motion->start();
	_ishit = false;
	_pushp = 0;

	return S_OK;
}

void Fish::update()
{
	pybullet();
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

void Fish::render(HDC hdc)
{
	if (_weaponReady == true)_readyWeapon->render(hdc);
	_img->aniRender(hdc, _pt.x - _img->getFrameWidth() / 2, _pt.y - _img->getFrameHeight() / 2, _motion);
	_currentWeapon->render(hdc);
}

void Fish::setAnimation()
{
	fishidleright = new animation;
	fishidleright->init("fish_idle");
	fishidleright->setPlayFrame(0, 3, false, true);
	fishidleright->setFPS(10);

	fishidleleft = new animation;
	fishidleleft->init("fish_idle");
	fishidleleft->setPlayFrame(7, 4, false, true);
	fishidleleft->setFPS(10);

	fishwalkright = new animation;
	fishwalkright->init("fish_walk");
	fishwalkright->setPlayFrame(0, 5, false, true);
	fishwalkright->setFPS(10);

	fishwalkleft = new animation;
	fishwalkleft->init("fish_walk");
	fishwalkleft->setPlayFrame(11, 6, false, true);
	fishwalkleft->setFPS(10);

	fishhitright = new animation;
	fishhitright->init("fish_hit");
	fishhitright->setPlayFrame(0, 2, false, false, righthurt, this);
	fishhitright->setFPS(8);

	fishhitleft = new animation;
	fishhitleft->init("fish_hit");
	fishhitleft->setPlayFrame(3, 2, false, false, lefthurt, this);
	fishhitleft->setFPS(10);

	fishdead = new animation;
	fishdead->init("fish_dead");
	fishdead->setPlayFrame(0, 3, false, false);//콜백필요
	fishdead->setFPS(8);


}

void Fish::contral()
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
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		_movedirctionx = NOMOVE;
	}
	if (KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S'))
	{
		_movedirctiony = NOMOVE;
	}


	if (_playerstate == IDLE && !_ishit)
	{
		if (_direction == LEFT)
		{
			_img = IMAGEMANAGER->findImage("fish_idle");
			_motion = fishidleleft;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
		else
		{
			_img = IMAGEMANAGER->findImage("fish_idle");
			_motion = fishidleright;
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
				_movedirctionx = LEFTMOVE;

			}
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				_pt.x += 5;
				_movedirctionx = RIGHTMOVE;
			}
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				_pt.y -= 5;
				_movedirctiony = UPMOVE;
			}
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				_pt.y += 5;
				_movedirctiony = DOWNMOVE;
			}
		}

		if (!_ishit)
		{
		if (_direction == LEFT)
		{
			_img = IMAGEMANAGER->findImage("fish_walk");
			_motion = fishwalkleft;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
		else
		{
			_img = IMAGEMANAGER->findImage("fish_walk");
			_motion = fishwalkright;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}

		}
	}
	if (_ishit)
	{
		if (_direction == LEFT)
		{
			_img = IMAGEMANAGER->findImage("fish_hit");
			_motion = fishhitright;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
		else
		{
			_img = IMAGEMANAGER->findImage("fish_hit");
			_motion = fishhitleft;
			if (!_motion->isPlay())
			{
				_motion->start();
			}
		}
	}
	//================================================= 
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{

		if (_weaponReady) playerWeaponSwap();
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (_weaponReady == true) ITEMMANAGER->weaponSwap();
		if (_weaponReady == false) ITEMMANAGER->grabWeapon();
	}

	if (_hp <= 0 && !_isStrongSpirit)
	{
		_playerstate = DEAD;
		_img = IMAGEMANAGER->findImage("fish_dead");
		_motion = fishdead;
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

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _playerstate == WALK)
	{
		_isdash = true;
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
	if (_isdash)
	{
		if (_movedirctionx == RIGHTMOVE)
		{
			_pushp++;
			_pt.x += 15 - _pushp;
			if (_pushp == 15)
			{
				_isdash = false;
				_pushp = 0;
			}
		}
		if (_movedirctionx == LEFTMOVE)
		{
			_pushp++;
			_pt.x -= 15 - _pushp;
			if (_pushp == 15)
			{
				_isdash = false;
				_pushp = 0;
			}
		}

		if (_movedirctiony == UPMOVE)
		{
			_pushp++;
			_pt.y -= 15 - _pushp;
			if (_pushp == 15)
			{
				_isdash = false;
				_pushp = 0;
			}
		}
		if (_movedirctiony == DOWNMOVE)
		{
			_pushp++;
			_pt.y += 15 - _pushp;
			if (_pushp == 15)
			{
				_isdash = false;
				_pushp = 0;
			}
		}
	}



}

void Fish::righthurt(void * obj)
{
	Fish*f = (Fish*)obj;
	f->setIshit(false);

}


void Fish::lefthurt(void * obj)
{
	Fish*f = (Fish*)obj;
	f->setIshit(false);

}

void Fish::makeDead(void * obj)
{
	Fish*f = (Fish*)obj;
}
