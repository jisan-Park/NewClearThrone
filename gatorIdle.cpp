#include "stdafx.h"
#include "gatorIdle.h"

HRESULT gatorIdle::init(enemyinfo info)
{
	gatoridleright = new animation;
	gatoridleright->init("gator_idle");
	gatoridleright->setPlayFrame(0, 7, false, true);
	gatoridleright->setFPS(10);

	gatoridleleft = new animation;
	gatoridleleft->init("gator_idle");
	gatoridleleft->setPlayFrame(15, 8, false, true);
	gatoridleleft->setFPS(10);

	gatorhurtright = new animation;
	gatorhurtright->init("gator_hurt");
	gatorhurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	gatorhurtright->setFPS(10);

	gatorhurtleft = new animation;
	gatorhurtleft->init("gator_hurt");
	gatorhurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	gatorhurtleft->setFPS(10);


	_img = IMAGEMANAGER->findImage("gator_idle");
	if (info.direction == E_LEFT) _motion = gatoridleleft;
	if (info.direction == E_RIGHT)_motion = gatoridleright;
	_pt = info.pt;

	return S_OK;
}

void gatorIdle::update(enemyinfo & info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		SOUNDMANAGER->play("¿¡³Ê¹ÌÈý1", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("gator_hurt");
		if (info.direction == E_LEFT) _motion = gatorhurtleft;
		if (info.direction == E_RIGHT)_motion = gatorhurtright;

	}
	else
	{
		_img = IMAGEMANAGER->findImage("gator_idle");
		if (info.direction == E_LEFT) _motion = gatoridleleft;
		if (info.direction == E_RIGHT)_motion = gatoridleright;

	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
