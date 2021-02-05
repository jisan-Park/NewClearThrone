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
