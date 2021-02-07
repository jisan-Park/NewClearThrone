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

float enemy::EtoPAngleRnd()
{
	float rndAngle;
	int rnd;

	rnd = RND->getFromIntTo(1, 8);
	if (rnd < 3)
	{
		rndAngle = getAngle(_info.pt, PLAYERMANAGER->getPlayer()->getPt()) + 0.15f;
	}
	else if (3 <= rnd && rnd < 6)
	{
		rndAngle = getAngle(_info.pt, PLAYERMANAGER->getPlayer()->getPt());
	}
	else
	{
		rndAngle = getAngle(_info.pt, PLAYERMANAGER->getPlayer()->getPt()) - 0.15f;
	}

	return rndAngle;
}

float enemy::EtoPAngleRnd2()
{
	return 0.0f;
}

void enemy::eyeSkill(int x, int y)
{
	if (_info.pt.x < x) _info.pt.x += 1;
	if (_info.pt.x > x) _info.pt.x -= 1;
	if (_info.pt.y < y) _info.pt.y += 1;
	if (_info.pt.y > y) _info.pt.y -= 1;
}

void enemy::plantSkill(RECT rc)
{
	RECT temp;
	if (IntersectRect(&temp, &rc, &_info.rc))
	{
		_info.speed = 0;
	}
	else _info.speed = _info.originSpeed;
}

void enemy::plantBulletCollision()
{
	RECT temp;
	if (IntersectRect(&temp, &_info.rc, &PLANTBULLET->getRC()))
	{
		PLANTBULLET->setISfire(false);
		PLANTBULLET->setImage(IMAGEMANAGER->findImage("plant_skill"));
		PLANTBULLET->setMotion();
	}
}

void enemy::collision()
{
	if (_info.state != E_DEAD)
	{
		for (int i = 0; i < BULLETMANAGER->getvPlayerBullet().size(); ++i)
		{
			RECT temp;
			if (IntersectRect(&temp, &BULLETMANAGER->getvPlayerBullet()[i]->getRect(), &_info.rc))
			{
				PLAYERMANAGER->getPlayer()->Bloodlustupdate();
				PLAYERMANAGER->getPlayer()->RecycleGlandate();
				_info.isHurt = true;
				_info.hp -= BULLETMANAGER->getvPlayerBullet()[i]->getDamage();
				_info.pt.x += cosf(BULLETMANAGER->getvPlayerBullet()[i]->getAngle()) * 10;
				_info.pt.y += -sinf(BULLETMANAGER->getvPlayerBullet()[i]->getAngle()) * 10;
				BULLETMANAGER->removePlayerBullet(i);
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

void enemy::explosion(POINT pt, float range, int damage)
{
	if (_info.state != E_DEAD)
	{
		if (getDistance(_info.pt, pt) < range)
		{
			_info.isHurt = true;
			_info.hp -= damage;
			_info.pt.x += cosf(getAngle(_info.pt, pt)) * 20;
			_info.pt.y += -sinf(getAngle(_info.pt, pt)) * 20;
		}
	}
}

void enemy::meleecollision(POINT pt, float range, int damage)
{
	if (_info.state != E_DEAD)
	{
		if (getDistance(_info.pt, pt) < range)
		{
			_info.isHurt = true;
			_info.hp -= damage;
			_info.pt.x += cosf(getAngle(_info.pt, pt)) * 10;
			_info.pt.y += -sinf(getAngle(_info.pt, pt)) * 10;
		}
	}
}