#include "stdafx.h"
#include "scolpionIdle.h"

HRESULT scolpionIdle::init(enemyinfo info)
{
	scolpionidleright = new animation;
	scolpionidleright->init("scolpion_idle");
	scolpionidleright->setPlayFrame(0, 3, false, true);
	scolpionidleright->setFPS(10);

	scolpionidleleft = new animation;
	scolpionidleleft->init("scolpion_idle");
	scolpionidleleft->setPlayFrame(7, 4, false, true);
	scolpionidleleft->setFPS(10);

	scolpionhurtright = new animation;
	scolpionhurtright->init("scolpion_hurt");
	scolpionhurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	scolpionhurtright->setFPS(10);

	scolpionhurtleft = new animation;
	scolpionhurtleft->init("scolpion_hurt");
	scolpionhurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	scolpionhurtleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("scolpion_idle");
	if (info.direction == E_LEFT) _motion = scolpionidleleft;
	if (info.direction == E_RIGHT) _motion = scolpionidleright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void scolpionIdle::update(enemyinfo & info)
{
	_pt = info.pt;
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
		_img = IMAGEMANAGER->findImage("scolpion_idle");
		if (info.direction == E_LEFT) _motion = scolpionidleleft;
		if (info.direction == E_RIGHT) _motion = scolpionidleright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
