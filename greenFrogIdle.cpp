#include "stdafx.h"
#include "greenFrogIdle.h"

HRESULT greenFrogIdle::init(enemyinfo info)
{
	greenfrogidleright = new animation;
	greenfrogidleright->init("greenfrog_idle");
	greenfrogidleright->setPlayFrame(0, 3, false, true);
	greenfrogidleright->setFPS(10);

	greenfrogidleleft = new animation;
	greenfrogidleleft->init("greenfrog_idle");
	greenfrogidleleft->setPlayFrame(6, 4, false, true);
	greenfrogidleleft->setFPS(10);

	greenfroghurtright = new animation;
	greenfroghurtright->init("greenfrog_hurt");
	greenfroghurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	greenfroghurtright->setFPS(10);

	greenfroghurtleft = new animation;
	greenfroghurtleft->init("greenfrog_hurt");
	greenfroghurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	greenfroghurtleft->setFPS(10);


	_pt = info.pt;

	_img = IMAGEMANAGER->findImage("greenfrog_idle");
	if (info.direction == E_LEFT) _motion = greenfrogidleleft;
	if (info.direction == E_RIGHT)_motion = greenfrogidleright;

	_motion->start();

	return S_OK;
}

void greenFrogIdle::update(enemyinfo & info)
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
		_img = IMAGEMANAGER->findImage("greenfrog_hurt");
		if (info.direction == E_LEFT) _motion = greenfroghurtleft;
		if (info.direction == E_RIGHT)_motion = greenfroghurtright;

	}
	else
	{
		_img = IMAGEMANAGER->findImage("greenfrog_idle");
		if (info.direction == E_LEFT) _motion = greenfrogidleleft;
		if (info.direction == E_RIGHT)_motion = greenfrogidleright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
