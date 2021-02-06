#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init(float x, float y)
{
	return S_OK;
}

void enemy::update()
{
}

void enemy::release()
{
}

void enemy::render(HDC hdc)
{
	//_img->aniRender(hdc, _x, _y, _motion);
}

void enemy::attack()
{
}

void enemy::move()
{
}

void enemy::setAnimation()
{
}

void enemy::setState(ENEMYSTATE state)
{

}

bool enemy::inRange()
{
	if (getDistance(PLAYERMANAGER->getPlayer()->getPt(), _info.pt) < _info.noticeRange) return true;
	else return false;
}

float enemy::EtoPAngle()
{
	return getAngle(_info.pt, PLAYERMANAGER->getPlayer()->getPt());
}

void enemy::collision()
{
	if (_info.state != E_DEAD)
	{
		for (int i = 0; i < BULLETMANAGER->getvBullet().size(); ++i)
		{
			RECT temp;
			if (IntersectRect(&temp, &BULLETMANAGER->getvBullet()[i]->getRect(), &_info.rc) && BULLETMANAGER->getvBullet()[i]->getWho() == PLAYER)
			{
				_info.isHurt = true;
				_info.hp -= BULLETMANAGER->getvBullet()[i]->getDamage();
				_info.pt.x += cosf(BULLETMANAGER->getvBullet()[i]->getAngle()) * 10;
				_info.pt.y += -sinf(BULLETMANAGER->getvBullet()[i]->getAngle()) * 10;
				BULLETMANAGER->removeBullet(i);
				break;
			}
		}
	}
	//for (PLAYERMANAGER->getPlayer()->getWeapon()->getBullet()->getViBullet() = PLAYERMANAGER->getPlayer()->getWeapon()->getBullet()->getVbullet().begin();
	//	PLAYERMANAGER->getPlayer()->getWeapon()->getBullet()->getViBullet() != PLAYERMANAGER->getPlayer()->getWeapon()->getBullet()->getVbullet().end();)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp, &PLAYERMANAGER->getPlayer()->getWeapon()->getBullet()->getViBullet()->rc, &_info.rc))
	//	{
	//		PLAYERMANAGER->getPlayer()->getWeapon()->getBullet()->getVbullet().erase;
	//		_info.nextState = E_HURT;
	//	}
	//}
}
