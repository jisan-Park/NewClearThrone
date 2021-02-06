#include "stdafx.h"
#include "banditIdle.h"
#include "bandit.h"

HRESULT banditIdle::init(enemyinfo info)
{
	banditidleright = new animation;
	banditidleright->init("bandit_idle");
	banditidleright->setPlayFrame(0, 3, false, true);
	banditidleright->setFPS(10);

	banditidleleft = new animation;
	banditidleleft->init("bandit_idle");
	banditidleleft->setPlayFrame(7, 4, false, true);
	banditidleleft->setFPS(10);

	bandithurtright = new animation;
	bandithurtright->init("bandit_hurt");
	bandithurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	bandithurtright->setFPS(10);

	bandithurtleft = new animation;
	bandithurtleft->init("bandit_hurt");
	bandithurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	bandithurtleft->setFPS(10);

	_pt = info.pt;
	_img = IMAGEMANAGER->findImage("bandit_idle");
	if (info.direction == E_LEFT) _motion = banditidleleft;
	if (info.direction == E_RIGHT) _motion = banditidleright;
	_motion->start();

	return S_OK;
}

void banditIdle::update(enemyinfo &info)
{
	_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		SOUNDMANAGER->play("Àâ¸÷ Á×À»¶§1", GAMEMANAGER->getSfxVolume());
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("bandit_hurt");
		if (info.direction == E_LEFT) _motion = bandithurtleft;
		if (info.direction == E_RIGHT) _motion = bandithurtright;
	}
	else
	{
		_img = IMAGEMANAGER->findImage("bandit_idle");
		if (info.direction == E_LEFT) _motion = banditidleleft;
		if (info.direction == E_RIGHT) _motion = banditidleright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

