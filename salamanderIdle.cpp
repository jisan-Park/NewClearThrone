#include "stdafx.h"
#include "salamanderIdle.h"

HRESULT salamanderIdle::init(enemyinfo info)
{
	salamanderidleright = new animation;
	salamanderidleright->init("salamander_idle");
	salamanderidleright->setPlayFrame(0, 6, false, true);
	salamanderidleright->setFPS(10);

	salamanderidleleft = new animation;
	salamanderidleleft->init("salamander_idle");
	salamanderidleleft->setPlayFrame(13, 7, false, true);
	salamanderidleleft->setFPS(10);

	salamanderhurtright = new animation;
	salamanderhurtright->init("salamander_hurt");
	salamanderhurtright->setPlayFrame(0, 2, false, false);
	salamanderhurtright->setFPS(10);

	salamanderhurtleft = new animation;
	salamanderhurtleft->init("salamander_hurt");
	salamanderhurtleft->setPlayFrame(5, 3, false, false);
	salamanderhurtleft->setFPS(10);
	_img = IMAGEMANAGER->findImage("salamander_idle");
	if (info.direction == E_LEFT) _motion = salamanderidleleft;
	if (info.direction == E_RIGHT) _motion = salamanderidleright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void salamanderIdle::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
