#include "stdafx.h"
#include "assassinIdle.h"


HRESULT assassinIdle::init(enemyinfo info)
{
	assassinfakeright = new animation;
	assassinfakeright->init("assassin_fake");
	assassinfakeright->setPlayFrame(0, 5, false, true);
	assassinfakeright->setFPS(10);

	assassinfakeleft = new animation;
	assassinfakeleft->init("assassin_fake");
	assassinfakeleft->setPlayFrame(11, 6, false, true);
	assassinfakeleft->setFPS(10);

	assassinidleright = new animation;
	assassinidleright->init("assassin_idle");
	assassinidleright->setPlayFrame(0, 3, false, true);
	assassinidleright->setFPS(10);

	assassinidleleft = new animation;
	assassinidleleft->init("assassin_idle");
	assassinidleleft->setPlayFrame(7, 4, false, true);
	assassinidleleft->setFPS(10);

	assassinhurtright = new animation;
	assassinhurtright->init("assassin_hurt");
	assassinhurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	assassinhurtright->setFPS(10);

	assassinhurtleft = new animation;
	assassinhurtleft->init("assassin_hurt");
	assassinhurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	assassinhurtleft->setFPS(10);


	_pt = info.pt;
	_img = IMAGEMANAGER->findImage("assassin_fake");
	if (info.direction == E_LEFT) _motion = assassinfakeleft;
	if (info.direction == E_RIGHT) _motion = assassinfakeright;
	_motion->start();
	return S_OK;
	

}

void assassinIdle::update(enemyinfo & info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		SOUNDMANAGER->play("���ʹ���1", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("assassin_hurt");
		if (info.direction == E_LEFT) _motion = assassinhurtleft;
		if (info.direction == E_RIGHT) _motion = assassinhurtright;
	}
	else
	{
		if (128 > getDistance(info.pt, PLAYERMANAGER->getPlayer()->getPt()))
		{
			_img = IMAGEMANAGER->findImage("assassin_idle");
			if (info.direction == E_LEFT) _motion = assassinidleleft;
			if (info.direction == E_RIGHT) _motion = assassinidleright;
		
		}
		else {
	
			_img = IMAGEMANAGER->findImage("assassin_fake");
			if (info.direction == E_LEFT) _motion = assassinfakeleft;
			if (info.direction == E_RIGHT) _motion = assassinfakeright;
		}
	
		
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
