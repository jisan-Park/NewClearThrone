#include "stdafx.h"
#include "bulletManager.h"

HRESULT bulletManager::init()
{
	return S_OK;
}

void bulletManager::release()
{
}

void bulletManager::update()
{
	//for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	//{
	//	if ((*_viBullet)->getGone() == true) (*_vBullet).erase()
	//	(*_viBullet)->update();
	//	++_viBullet
	//}
	for (int i = 0; i < _vEnemyBullet.size();)
	{
		if (_vEnemyBullet[i]->getGone() == true)
		{
			removeEnemyBullet(i);
			break;
		}
		_vEnemyBullet[i]->update();
		++i;
	}
	for (int i = 0; i < _vPlayerBullet.size();)
	{
		if (_vPlayerBullet[i]->getGone() == true)
		{
			removePlayerBullet(i);
			break;
		}
		_vPlayerBullet[i]->update();
		++i;
	}
}

void bulletManager::render(HDC hdc)
{
	for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
	{
		(*_viEnemyBullet)->render(hdc);
	}
	for (_viPlayerBullet = _vPlayerBullet.begin(); _viPlayerBullet != _vPlayerBullet.end(); ++_viPlayerBullet)
	{
		(*_viPlayerBullet)->render(hdc);
	}
}

void bulletManager::PlayerFire(BULLETTYPE type, POINT pt, float speed, float angle, int damage)
{
	bullet* temp;
	switch (type)
	{
	case ANGLE16:
	{
		temp = new bullet16;
		temp->fire(pt, speed, angle, damage);
	}
	break;
	case ANGLE1:
	{
		temp = new bullet1;
		temp->fire(pt, speed, angle, damage);
	}
	break;
	case FLAME:
		break;
	default:
	case GRENADE:
	{
		temp = new grenade;
		temp->fire(pt, speed, angle, damage);
	}
	break;
	}
	_vPlayerBullet.push_back(temp);
}

void bulletManager::EnemyFire(BULLETTYPE type, POINT pt, float speed, float angle, int damage)
{
	bullet* temp;
	switch (type)
	{
	case ANGLE16:
	{
		temp = new bullet16;
		temp->fire(pt, speed, angle, damage);
	}
	break;
	case ANGLE1:
	{
		temp = new bullet1;
		temp->fire(pt, speed, angle, damage);
	}
	break;
	case FLAME:
		break;
	default:
	case GRENADE:
	{
		temp = new grenade;
		temp->fire(pt, speed, angle, damage);
	}
	break;
	}
	_vEnemyBullet.push_back(temp);
}

void bulletManager::removePlayerBullet(int i)
{
	_vPlayerBullet.erase(_vPlayerBullet.begin() + i);
}

void bulletManager::removeEnemyBullet(int i)
{
	_vEnemyBullet.erase(_vEnemyBullet.begin() + i);
}
