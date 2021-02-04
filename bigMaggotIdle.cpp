#include "stdafx.h"
#include "bigMaggotIdle.h"

HRESULT bigMaggotIdle::init(enemyinfo info)
{
	bigmaggotidleright = new animation;
	bigmaggotidleright->init("bigmaggot_idle");
	bigmaggotidleright->setPlayFrame(0, 5, false, true);
	bigmaggotidleright->setFPS(10);

	bigmaggotidleleft = new animation;
	bigmaggotidleleft->init("bigmaggot_idle");
	bigmaggotidleleft->setPlayFrame(11, 6, false, true);
	bigmaggotidleleft->setFPS(10);

	bigmaggothurtright = new animation;
	bigmaggothurtright->init("bigmaggot_hurt");
	bigmaggothurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	bigmaggothurtright->setFPS(10);

	bigmaggothurtleft = new animation;
	bigmaggothurtleft->init("bigmaggot_hurt");
	bigmaggothurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	bigmaggothurtleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("bigmaggot_idle");

	if (info.direction == E_LEFT) _motion = bigmaggotidleleft;
	if (info.direction == E_RIGHT) _motion = bigmaggotidleright;
	_motion->start();
	_pt = info.pt;

	return S_OK;
}

void bigMaggotIdle::update(enemyinfo & info)
{

	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	_pt = info.pt;
	if (isHurt == true)
	{
		_img = IMAGEMANAGER->findImage("bigmaggot_hurt");
		if (info.direction == E_LEFT) _motion = bigmaggothurtleft;
		if (info.direction == E_RIGHT) _motion = bigmaggothurtright;
	}
	else
	{

		info.pt.x += cosf(info.moveAngle)* info.speed;
		info.pt.y += -sinf(info.moveAngle)* info.speed;

		_img = IMAGEMANAGER->findImage("bigmaggot_idle");
		if (info.direction == E_LEFT) _motion = bigmaggotidleleft;
		if (info.direction == E_RIGHT) _motion = bigmaggotidleright;
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
