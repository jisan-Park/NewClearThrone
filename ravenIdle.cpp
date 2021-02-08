#include "stdafx.h"
#include "ravenIdle.h"

HRESULT ravenIdle::init(enemyinfo info)
{
	ravenidleright = new animation;
	ravenidleright->init("raven_idle");
	ravenidleright->setPlayFrame(0, 8, false, true);
	ravenidleright->setFPS(10);

	ravenidleleft = new animation;
	ravenidleleft->init("raven_idle");
	ravenidleleft->setPlayFrame(15, 9, false, true);
	ravenidleleft->setFPS(10);

	ravenhurtright = new animation;
	ravenhurtright->init("raven_hurt");
	ravenhurtright->setPlayFrame(0, 2, false, false, hurtFinish,this);
	ravenhurtright->setFPS(10);

	ravenhurtleft = new animation;
	ravenhurtleft->init("raven_hurt");
	ravenhurtleft->setPlayFrame(5, 3, false, false, hurtFinish,this);
	ravenhurtleft->setFPS(10);


	_img = IMAGEMANAGER->findImage("raven_idle");
	if (info.direction == E_LEFT) _motion = ravenidleleft;
	if (info.direction == E_RIGHT) _motion = ravenidleright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void ravenIdle::update(enemyinfo & info)
{
	_pt = info.pt;

	if (info.isHurt == true)
	{
		isHurt = true;
		SOUNDMANAGER->play("±î¸¶±Í¸ÂÀ½", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
		info.isHurt = false;
	}
	_pt = info.pt;
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("raven_hurt");
		if (info.direction == E_LEFT) _motion = ravenhurtleft;
		if (info.direction == E_RIGHT) _motion = ravenhurtright;
	}
	else
	{
		_img = IMAGEMANAGER->findImage("raven_idle");

		if (PLAYERMANAGER->getPlayer()->getPt().x < info.pt.x)
		{
			info.direction == E_LEFT;
			_motion = ravenidleleft;

		}
		if (PLAYERMANAGER->getPlayer()->getPt().x > info.pt.x)
		{
			info.direction == E_RIGHT;
			_motion = ravenidleright;

		}

	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
