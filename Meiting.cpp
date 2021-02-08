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
	_img = IMAGEMANAGER->findImage("melting_idle");
	_motion = meltingidleright;
	_motion->start();
	_ishit = false;
	return S_OK;
}

void Meiting::update()
{
	pybullet();
	if (_hp > _maxhp)
	{
		_hp = _maxhp;
	}
	contral();
	//collision();
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
	meltingdead->setPlayFrame(0, 3, false, false);//ÄÝ¹éÇÊ¿ä
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
	
	if (_hp <= 0 && !_isStrongSpirit)
	{
		_playerstate = DEAD;
		_img = IMAGEMANAGER->findImage("melting_dead");
		_motion = meltingdead;
		if (!_motion->isPlay())
		{
			SOUNDMANAGER->play("¸áÆÃ»ç¸Á", GAMEMANAGER->getMusicVolume() * GAMEMANAGER->getMasterVolume());
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
		if (!SOUNDMANAGER->isPlaySound("Æø¹ß»ç¿îµå"))
		{ 
			SOUNDMANAGER->play("Æø¹ß»ç¿îµå", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
		}
		for (int i = 0; i < ENEMYMANAGER->getShowEnemyVector().size(); ++i)
		{
			if (ENEMYMANAGER->getShowEnemyVector()[i]->getInfo().state != DEAD) continue;
			for (int j = 0; j < ENEMYMANAGER->getShowEnemyVector().size(); ++j)
			{
				ENEMYMANAGER->getShowEnemyVector()[j]->explosion(ENEMYMANAGER->getShowEnemyVector()[i]->getInfo().pt, 100, 20);
				
			}
			EFFECTMANAGER->play("exp", ENEMYMANAGER->getShowEnemyVector()[i]->getInfo().pt.x, ENEMYMANAGER->getShowEnemyVector()[i]->getInfo().pt.y);
			ENEMYMANAGER->removeEnemy(i);
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

void Meiting::righthurt(void * obj)
{
	Meiting*f = (Meiting*)obj;
	f->setIshit(false);
	
}

void Meiting::lefthurt(void * obj)
{
	Meiting*f = (Meiting*)obj;
	f->setIshit(false);
	
}

void Meiting::makeDead(void * obj)
{
}
