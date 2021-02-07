#include "stdafx.h"
#include "salamanderFire.h"

HRESULT salamanderFire::init(enemyinfo info)
{
	salamanderfireright = new animation;
	salamanderfireright->init("salamander_fire");
	salamanderfireright->setPlayFrame(0, 1, false, false);
	salamanderfireright->setFPS(10);

	salamanderfireleft = new animation;
	salamanderfireleft->init("salamander_fire");
	salamanderfireleft->setPlayFrame(3, 2, false, false);
	salamanderfireleft->setFPS(10);

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
	return S_OK;
}

void salamanderFire::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
