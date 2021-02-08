#include "stdafx.h"
#include "bulletManager.h"

HRESULT bulletManager::init()
{
	_isScareFace = false;
	_isEuphoria = false;
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
	wallCollision();
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
	if (!_isScareFace)
	{
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
		case GRENADE:
		{
			temp = new grenade;
			temp->fire(pt, speed, angle, damage);
		}

		break;
		case SHOTGUNBULLET:
		{
			temp = new shotGunBullet;
			temp->fire(pt, speed, angle, damage);
		}
		case LASERBULLET:
		{
			temp = new laserBullet;
			temp->fire(pt, speed, angle, damage);
		}
		break;
		case E_ANGLE16_1:
		{
			temp = new enemyBullet16_1;
			temp->fire(pt, speed, angle, damage);
		}
		break;
		case E_ANGLE16_2:
		{
			temp = new enemyBullet16_2;
			temp->fire(pt, speed, angle, damage);
		}
		break;
		case E_SHOTGUN:
		{
			temp = new enemyShotGun;
			temp->fire(pt, speed, angle, damage);
		}
		break;
		case E_SHOTGUN2:
		{
			temp = new enemyShotGun2;
			temp->fire(pt, speed, angle, damage);
		}
		default:
			break;
		}
	}
	else
	{
		switch (type)
		{
		case ANGLE16:
		{
			temp = new bullet16;
			temp->fire(pt, speed, angle, damage*1.2);
		}
		break;
		case ANGLE1:
		{
			temp = new bullet1;
			temp->fire(pt, speed, angle, damage*1.2);
		}
		break;
		case FLAME:
			break;
		case GRENADE:
		{
			temp = new grenade;
			temp->fire(pt, speed, angle, damage*1.2);
		}

		break;
		case SHOTGUNBULLET:
		{
			temp = new shotGunBullet;
			temp->fire(pt, speed, angle, damage*1.2);
		}
		case LASERBULLET:
		{
			temp = new laserBullet;
			temp->fire(pt, speed, angle, damage*1.2);
		}
		break;
		case E_ANGLE16_1:
		{
			temp = new enemyBullet16_1;
			temp->fire(pt, speed, angle, damage*1.2);
		}
		break;
		case E_ANGLE16_2:
		{
			temp = new enemyBullet16_2;
			temp->fire(pt, speed, angle, damage*1.2);
		}
		break;
		case E_SHOTGUN:
		{
			temp = new enemyShotGun;
			temp->fire(pt, speed, angle, damage*1.2);
		}
		break;
		case E_SHOTGUN2:
		{
			temp = new enemyShotGun2;
			temp->fire(pt, speed, angle, damage*1.2);
		}
		default:
			break;
		}
	}
	_vPlayerBullet.push_back(temp);
}

void bulletManager::EnemyFire(BULLETTYPE type, POINT pt, float speed, float angle, int damage)
{
	bullet* temp;

	if (!_isEuphoria)
	{
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
		case GRENADE:
		{
			temp = new grenade;
			temp->fire(pt, speed, angle, damage);
		}
		break;
		case E_ANGLE16_1:
		{
			temp = new enemyBullet16_1;
			temp->fire(pt, speed, angle, damage);
		}
		break;
		case E_ANGLE16_2:
		{
			temp = new enemyBullet16_2;
			temp->fire(pt, speed, angle, damage);
		}
		break;
		case E_SHOTGUN:
		{
			temp = new enemyShotGun;
			temp->fire(pt, speed, angle, damage);
		}
		break;
		case E_SHOTGUN2:
		{
			temp = new enemyShotGun2;
			temp->fire(pt, speed, angle, damage);
		}
		break;
		}
	}
	else
	{
		switch (type)
		{
		case ANGLE16:
		{
			temp = new bullet16;
			temp->fire(pt, speed*0.9, angle, damage);
		}
		break;
		case ANGLE1:
		{
			temp = new bullet1;
			temp->fire(pt, speed*0.9, angle, damage);
		}
		break;
		case FLAME:
			break;
		case GRENADE:
		{
			temp = new grenade;
			temp->fire(pt, speed*0.9, angle, damage);
		}
		break;
		case E_ANGLE16_1:
		{
			temp = new enemyBullet16_1;
			temp->fire(pt, speed*0.9, angle, damage);
		}
		break;
		case E_ANGLE16_2:
		{
			temp = new enemyBullet16_2;
			temp->fire(pt, speed*0.9, angle, damage);
		}
		break;
		case E_SHOTGUN:
		{
			temp = new enemyShotGun;
			temp->fire(pt, speed*0.9, angle, damage);
		}
		break;
		case E_SHOTGUN2:
		{
			temp = new enemyShotGun2;
			temp->fire(pt, speed*0.9, angle, damage);
		}
		break;
		}
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

void bulletManager::wallCollision()
{
	for (int i = 0; i < _vPlayerBullet.size();)
	{
		if (MAPMANAGER->ptIntersect(_vPlayerBullet[i]->getPt()))
		{
			if (BULLETMANAGER->getvPlayerBullet()[i]->getType() == GRENADE)
			{
				BULLETMANAGER->getvPlayerBullet()[i]->explode();
				BULLETMANAGER->removePlayerBullet(i);
				break;
			}
			removePlayerBullet(i);
			break;
		}
		++i;
	}
	for (int i = 0; i < _vEnemyBullet.size();)
	{
		if (MAPMANAGER->ptIntersect(_vEnemyBullet[i]->getPt()))
		{
			removeEnemyBullet(i);
			break;
		}
		++i;
	}
}
void bulletManager::Euphoria()
{
	_isEuphoria = true;
}

void bulletManager::ScareFace()
{
	_isScareFace = true;
}