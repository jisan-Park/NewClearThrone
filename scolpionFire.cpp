#include "stdafx.h"
#include "scolpionFire.h"

HRESULT scolpionFire::init(enemyinfo info)
{
	scolpionfireright = new animation;
	scolpionfireright->init("scolpion_fire");
	scolpionfireright->setPlayFrame(0, 1, false, false);
	scolpionfireright->setFPS(10);

	scolpionfireleft = new animation;
	scolpionfireleft->init("scolpion_fire");
	scolpionfireleft->setPlayFrame(3, 2, false, false);
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
		if (info.direction == E_LEFT) _motion = scolpionfireleft;
		if (info.direction == E_RIGHT) _motion = scolpionfireright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
