#include "stdafx.h"
#include "assassinIdle.h"


HRESULT assassinIdle::init(enemyinfo info)
{
	assassinfakeright = new animation;
	assassinfakeright->init("assassin_fake");
	assassinfakeright->setPlayFrame(0, 5, false, true);
	assassinfakeright->setFPS(10);

	assassinfakeleft = new animation;
	assassinfakeleft->init("assassin_fake");
	assassinfakeleft->setPlayFrame(11, 6, false, true);
	assassinfakeleft->setFPS(10);

	assassinidleright = new animation;
	assassinidleright->init("assassin_idle");
	assassinidleright->setPlayFrame(0, 3, false, true);
	assassinidleright->setFPS(10);

	assassinidleleft = new animation;
	assassinidleleft->init("assassin_idle");
	assassinidleleft->setPlayFrame(7, 4, false, true);
	assassinidleleft->setFPS(10);
	_img = IMAGEMANAGER->findImage("assassin_fake");
	if (info.direction == E_LEFT) _motion = assassinfakeleft;
	if (info.direction == E_RIGHT) _motion = assassinfakeright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
	

}

void assassinIdle::update(enemyinfo & info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
