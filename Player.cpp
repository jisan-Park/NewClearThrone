#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

HRESULT Player::init(float x, float y)
{
	_isBloodLust = false;
	_isRecycleGland = false;
	_isStrongSpirit = false;


	return S_OK;
}

void Player::update()
{
}

void Player::release()
{
}

void Player::render(HDC hdc)
{
}

void Player::attack()
{
}

void Player::move()
{
}

void Player::setAnimation()
{
}

void Player::playerWeaponSwap()
{
	weaponType temp;
	temp = _readyWeapon->getType();
	switch (_currentWeapon->getType())
	{
	case ASSULTRIFLE:		_readyWeapon = new assultRifle;
		break;
	case GRENADELAUNCHER:	_readyWeapon = new grenadeLauncher;
		break;
	case MACHINEGUN:		_readyWeapon = new machineGun;
		break;
	case PISTOL:			_readyWeapon = new pistol;
		break;
	case RAZERRIFLE:		_readyWeapon = new razerRifle;
		break;
	case SHOTGUN:			_readyWeapon = new shotGun;
		break;
	case SHOVEL:			_readyWeapon = new shovel;
		break;
	case SWORD:				_readyWeapon = new sword;
		break;
	case TRIPLEMACHINEGUN:	_readyWeapon = new triplemachinegun;
		break;
	case WRENCH:			_readyWeapon = new wrench;
		break;
	default:
		break;
	}

	switch (temp)
	{
	case ASSULTRIFLE:		_currentWeapon = new assultRifle;
		break;
	case GRENADELAUNCHER:	_currentWeapon = new grenadeLauncher;
		break;
	case MACHINEGUN:		_currentWeapon = new machineGun;
		break;
	case PISTOL:			_currentWeapon = new pistol;
		break;
	case RAZERRIFLE:		_currentWeapon = new razerRifle;
		break;
	case SHOTGUN:			_currentWeapon = new shotGun;
		break;
	case SHOVEL:			_currentWeapon = new shovel;
		break;
	case SWORD:				_currentWeapon = new sword;
		break;
	case TRIPLEMACHINEGUN:	_currentWeapon = new triplemachinegun;
		break;
	case WRENCH:			_currentWeapon = new wrench;
		break;
	default:
		break;
	}
	_readyWeapon->init(_pt, READYTOUSE);
	_currentWeapon->init(_pt, NOWUSING);
}

void Player::groundWeaponSwap(weaponType type)
{
	switch (type)
	{
	case ASSULTRIFLE:		_currentWeapon = new assultRifle;
		break;
	case GRENADELAUNCHER:	_currentWeapon = new grenadeLauncher;
		break;
	case MACHINEGUN:		_currentWeapon = new machineGun;
		break;
	case PISTOL:			_currentWeapon = new pistol;
		break;
	case RAZERRIFLE:		_currentWeapon = new razerRifle;
		break;
	case SHOTGUN:			_currentWeapon = new shotGun;
		break;
	case SHOVEL:			_currentWeapon = new shovel;
		break;
	case SWORD:				_currentWeapon = new sword;
		break;
	case TRIPLEMACHINEGUN:	_currentWeapon = new triplemachinegun;
		break;
	case WRENCH:			_currentWeapon = new wrench;
		break;
	default:
		break;
	}
	_currentWeapon->init(_pt, NOWUSING);
}

void Player::groundWeaponGet(weaponType type)
{
	switch (_currentWeapon->getType())
	{
	case ASSULTRIFLE:		_readyWeapon = new assultRifle;
		break;
	case GRENADELAUNCHER:	_readyWeapon = new grenadeLauncher;
		break;
	case MACHINEGUN:		_readyWeapon = new machineGun;
		break;
	case PISTOL:			_readyWeapon = new pistol;
		break;
	case RAZERRIFLE:		_readyWeapon = new razerRifle;
		break;
	case SHOTGUN:			_readyWeapon = new shotGun;
		break;
	case SHOVEL:			_readyWeapon = new shovel;
		break;
	case SWORD:				_readyWeapon = new sword;
		break;
	case TRIPLEMACHINEGUN:	_readyWeapon = new triplemachinegun;
		break;
	case WRENCH:			_readyWeapon = new wrench;
		break;
	default:
		break;
	}
	_readyWeapon->init(_pt, READYTOUSE);
	switch (type)
	{
	case ASSULTRIFLE:		_currentWeapon = new assultRifle;
		break;
	case GRENADELAUNCHER:	_currentWeapon = new grenadeLauncher;
		break;
	case MACHINEGUN:		_currentWeapon = new machineGun;
		break;
	case PISTOL:			_currentWeapon = new pistol;
		break;
	case RAZERRIFLE:		_currentWeapon = new razerRifle;
		break;
	case SHOTGUN:			_currentWeapon = new shotGun;
		break;
	case SHOVEL:			_currentWeapon = new shovel;
		break;
	case SWORD:				_currentWeapon = new sword;
		break;
	case TRIPLEMACHINEGUN:	_currentWeapon = new triplemachinegun;
		break;
	case WRENCH:			_currentWeapon = new wrench;
		break;
	default:
		break;
	}
	_currentWeapon->init(_pt, NOWUSING);
}

void Player::BackMuscle()
{
	_playerbulletMax += 50;
	_playerecplodbeMax += 50;
	_playerenergubMax += 50;
	_playershellbMax += 50;
}

void Player::Bloodlust()
{
	_isBloodLust = true;
}

void Player::EagleEyes()
{
	_angleCard += 1;
}

void Player::ExtraFeet()
{
	_speed += 2;
}

void Player::LastWish()
{
	_hp = _maxhp;
	_playerbullet = _playerbulletMax;
	_playerexplodeb = _playerecplodbeMax;
	_playerenergyb = _playerenergubMax;
	_playershellb = _playershellbMax;


}

void Player::RecycleGland()
{
	_isRecycleGland = true;
}

void Player::Rhinoskin()
{
	_maxhp += 4;
	_hp += 4;
}

void Player::Stress()
{
	_interval -= 3;
}

void Player::Strongspirit()
{
	_isStrongSpirit = true;
}

void Player::Bloodlustupdate()
{
	if (_isBloodLust)
	{
		int num;
		num = RND->getFromIntTo(0, 100);
		if (num < 5)
		{
			_hp += 1;
		}
	}
}

void Player::RecycleGlandate()
{
	if (_isRecycleGland)
	{
		int num;
		num = RND->getFromIntTo(0, 100);
		if (num < 61)
		{
			_playerbullet += 1;
			_playerexplodeb += 1;
			_playerenergyb += 1;
			_playershellb += 1;
		}
	}
}

void Player::collision()
{
	if (_playerstate != DEAD)
	{
		for (int i = 0; i < BULLETMANAGER->getvEnemyBullet().size(); ++i)
		{
			RECT temp;
			if (IntersectRect(&temp, &BULLETMANAGER->getvEnemyBullet()[i]->getRect(), &_rc) && !_ishit)
			{
				if (PLAYERMANAGER->getPlayerType() == CRYSTAL && _playerstate == SKILL) {
					switch (BULLETMANAGER->getvEnemyBullet()[i]->getType())
					{
					case ANGLE16:
					{
						BULLETMANAGER->PlayerFire(ANGLE16, _pt, BULLETMANAGER->getvEnemyBullet()[i]->getSpeed(), BULLETMANAGER->getvEnemyBullet()[i]->getAngle() - PI, 2);
					}
						break;
					case ANGLE1:
					{
						BULLETMANAGER->PlayerFire(ANGLE1, _pt, BULLETMANAGER->getvEnemyBullet()[i]->getSpeed(), BULLETMANAGER->getvEnemyBullet()[i]->getAngle() - PI, 2);
					}
						break;
					case FLAME:
					{
						BULLETMANAGER->PlayerFire(ANGLE16, _pt, BULLETMANAGER->getvEnemyBullet()[i]->getSpeed(), BULLETMANAGER->getvEnemyBullet()[i]->getAngle() - PI, 2);
					}
						break;
					case LASERBULLET:
					{
						BULLETMANAGER->PlayerFire(LASERBULLET, _pt, BULLETMANAGER->getvEnemyBullet()[i]->getSpeed(), BULLETMANAGER->getvEnemyBullet()[i]->getAngle() - PI, 2);
					}
						break;
					case E_ANGLE16_1:
					{
						BULLETMANAGER->PlayerFire(E_ANGLE16_1, _pt, BULLETMANAGER->getvEnemyBullet()[i]->getSpeed(), BULLETMANAGER->getvEnemyBullet()[i]->getAngle() - PI, 2);
					}
						break;
					case E_ANGLE16_2:
					{
						BULLETMANAGER->PlayerFire(E_ANGLE16_2, _pt, BULLETMANAGER->getvEnemyBullet()[i]->getSpeed(), BULLETMANAGER->getvEnemyBullet()[i]->getAngle() - PI, 2);
					}
						break;
					case E_SHOTGUN:
					{
						BULLETMANAGER->PlayerFire(E_SHOTGUN, _pt, BULLETMANAGER->getvEnemyBullet()[i]->getSpeed(), BULLETMANAGER->getvEnemyBullet()[i]->getAngle() - PI, 2);
					}
						break;
					case E_SHOTGUN2:
					{
						BULLETMANAGER->PlayerFire(E_SHOTGUN2, _pt, BULLETMANAGER->getvEnemyBullet()[i]->getSpeed(), BULLETMANAGER->getvEnemyBullet()[i]->getAngle() - PI, 2);
					}
						break;
					default:
						break;
					}
					BULLETMANAGER->removeEnemyBullet(i);
				}
				else
				{
					_ishit = true;
					_hp -= BULLETMANAGER->getvEnemyBullet()[i]->getDamage();
					BULLETMANAGER->removeEnemyBullet(i);
				}
				
				break;
			}
		}
		for (int i = 0; i < ENEMYMANAGER->getShowEnemyVector().size(); i++)
		{
			RECT temp;
			if (ENEMYMANAGER->getShowEnemyVector()[i]->getState() != E_DEAD &&IntersectRect(&temp, &ENEMYMANAGER->getShowEnemyVector()[i]->getRect(), &_rc) && !_ishit)
			{
				if (PLAYERMANAGER->getPlayerType() == CRYSTAL && _playerstate == SKILL)continue;
				_ishit = true;
				_hp -= 1;
				break;
			}
		}
	}
}


