#include "stdafx.h"
#include "salamanderFire.h"

HRESULT salamanderFire::init(enemyinfo info)
{
	salamanderfireright = new animation;
	salamanderfireright->init("salamander_fire");
	salamanderfireright->setPlayFrame(0, 1, false, false, fireFinish, this);
	salamanderfireright->setFPS(5);

	salamanderfireleft = new animation;
	salamanderfireleft->init("salamander_fire");
	salamanderfireleft->setPlayFrame(3, 2, false, false, fireFinish, this);
	salamanderfireleft->setFPS(5);

	salamanderhurtright = new animation;
	salamanderhurtright->init("salamander_hurt");
	salamanderhurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	salamanderhurtright->setFPS(10);

	salamanderhurtleft = new animation;
	salamanderhurtleft->init("salamander_hurt");
	salamanderhurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	salamanderhurtleft->setFPS(10);
	_img = IMAGEMANAGER->findImage("salamander_fire");
	if (info.direction == E_LEFT) _motion = salamanderfireleft;
	if (info.direction == E_RIGHT) _motion = salamanderfireright;
	_motion->start();
	_pt = info.pt;
	_flameAngle = -0.5;
	return S_OK;
}

void salamanderFire::update(enemyinfo & info)
{
	_pt = info.pt;

	if (isFire) {
		info.nextState = E_IDLE;
		isFire = false;
	}

	if (info.isHurt == true)
	{
		isHurt = true;
		SOUNDMANAGER->play("에너미힛2", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("salamander_hurt");
		if (info.direction == E_LEFT) _motion = salamanderhurtleft;
		if (info.direction == E_RIGHT) _motion = salamanderhurtright;
	}
	else
	{
		_img = IMAGEMANAGER->findImage("salamander_fire");
		////bullet 6발 angle random 으로 발사
		//fire_interval++;
		//if (fire_interval % 7 == 0) {
		//	for (int i = 0; i < 6; i++)
		//	{
		//		BULLETMANAGER->EnemyFire(E_ANGLE16_2, info.pt, info.speed, info.aimAngle - 0.7f + (i * 0.3f), 5);
		//	}
		//	fire_interval = 0;
		//}
		_cnt++;
		if (_cnt % 3 == 0) 
		{
			if (_flameAngle < 0.5f) _flameAngle += 0.1f;
			else if (_flameAngle > 0.6f) _flameAngle = 0;
			BULLETMANAGER->EnemyFire(FLAME, info.pt, 5, info.aimAngle - _flameAngle, 3);
			_cnt = 0;
		}

		if (PLAYERMANAGER->getPlayer()->getPt().x < info.pt.x)
		{
			info.direction = E_LEFT;
			_motion = salamanderfireleft;

		}
		if (PLAYERMANAGER->getPlayer()->getPt().x > info.pt.x)
		{
			info.direction = E_RIGHT;
			_motion = salamanderfireright;
		}

	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
