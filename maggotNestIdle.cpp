#include "stdafx.h"
#include "maggotNestIdle.h"

HRESULT maggotNestIdle::init(enemyinfo info)
{
	maggotnestidleright = new animation;
	maggotnestidleright->init("maggotnest_idle");
	maggotnestidleright->setPlayFrame(0,3, false, true);
	maggotnestidleright->setFPS(10);

	maggotnestidleleft = new animation;
	maggotnestidleleft->init("maggotnest_idle");
	maggotnestidleleft->setPlayFrame(7,4, false, true);
	maggotnestidleleft->setFPS(10);

	maggotnesthurtright = new animation;
	maggotnesthurtright->init("maggotnest_hurt");
	maggotnesthurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	maggotnesthurtright->setFPS(10);

	maggotnesthurtleft = new animation;
	maggotnesthurtleft->init("maggotnest_hurt");
	maggotnesthurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	maggotnesthurtleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("maggotnest_idle");
	if (info.direction == E_LEFT) _motion = maggotnestidleleft;
	if (info.direction == E_RIGHT) _motion = maggotnestidleright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void maggotNestIdle::update(enemyinfo & info)
{
	//_pt = info.pt;
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("maggotnest_hurt");
		if (info.direction == E_LEFT) _motion = maggotnesthurtleft;
		if (info.direction == E_RIGHT) _motion = maggotnesthurtright;
	}
	else
	{
		_img = IMAGEMANAGER->findImage("maggotnest_idle");
		if (info.direction == E_LEFT) _motion = maggotnestidleleft;
		if (info.direction == E_RIGHT) _motion = maggotnestidleright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);


	if (getDistance(PLAYERMANAGER->getPlayer()->getPt(), info.pt) < 100)
	{
		info.nextState = E_DEAD;
	}

}
