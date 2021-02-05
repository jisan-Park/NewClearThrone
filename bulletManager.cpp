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
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->update();
	}
}

void bulletManager::render(HDC hdc)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->render(hdc);
	}
}

void bulletManager::fire(BULLETTYPE type, POINT pt, float speed, float angle, int damage, whoshot who)
{
	bullet* temp;
	switch (type)
	{
	case ANGLE16:
	{
		temp = new bullet16;
		temp->fire(pt, speed, angle, damage, who);
	}
	break;
	case ANGLE1:
	{
		temp = new bullet1;
		temp->fire(pt, speed, angle, damage, who);
	}
	break;
	case FLAME:
		break;
	default:
		break;
	}
	_vBullet.push_back(temp);
}

void bulletManager::removeBullet(int i)
{
	_vBullet.erase(_vBullet.begin() + i);
}
