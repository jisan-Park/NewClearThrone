#include "stdafx.h"
#include "scolpionFire.h"

HRESULT scolpionFire::init(enemyinfo info)
{
	scolpionfireright = new animation;
	scolpionfireright->init("scolpion_fire");
	scolpionfireright->setPlayFrame(0, 1, false, false, fireFinish,this);
	scolpionfireright->setFPS(10);

	scolpionfireleft = new animation;
	scolpionfireleft->init("scolpion_fire");
	scolpionfireleft->setPlayFrame(3, 2, false, false,fireFinish,this);
	scolpionfireleft->setFPS(10);


	scolpionhurtright = new animation;
	scolpionhurtright->init("scolpion_hurt");
	scolpionhurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);

	scolpionhurtleft = new animation;
	scolpionhurtleft->init("scolpion_hurt");
	scolpionhurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	scolpionhurtleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("scolpion_fire");
	if (info.direction == E_LEFT) _motion = scolpionfireleft;
	if (info.direction == E_RIGHT) _motion = scolpionfireright;
	_motion->start();
	_pt = info.pt;

	return S_OK;
}

void scolpionFire::update(enemyinfo & info)
{
	_pt = info.pt;

	if (isFire) {
		info.nextState = E_IDLE;
		isFire = false;
	}

	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("scolpion_hurt");
		if (info.direction == E_LEFT) _motion = scolpionhurtleft;
		if (info.direction == E_RIGHT) _motion = scolpionhurtright;
	}
	else
	{
		_img = IMAGEMANAGER->findImage("scolpion_fire");
		//bullet 6발 angle random 으로 발사
		fire_interval ++;
		if (fire_interval % 7 == 0) {
			for (int i = 0; i < 6; i++)
			{
				BULLETMANAGER->EnemyFire(E_ANGLE16_2, info.pt, info.speed, info.aimAngle - 0.7f +(i * 0.3f), 5);
			}
			fire_interval = 0;
		}
		
		
		if (PLAYERMANAGER->getPlayer()->getPt().x < info.pt.x)
		{
			info.direction == E_LEFT;
			_motion = scolpionfireleft;

		}
		if (PLAYERMANAGER->getPlayer()->getPt().x > info.pt.x)
		{
			info.direction == E_RIGHT;
			_motion = scolpionfireright;
		}
		
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
