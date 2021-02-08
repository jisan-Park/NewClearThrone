#include "stdafx.h"
#include "ravenAppear.h"

HRESULT ravenAppear::init(enemyinfo info)
{
	isBurrowEnd = false;
	ravenlandright = new animation;
	ravenlandright->init("raven_land");
	ravenlandright->setPlayFrame(0, 3, false, false, appearidle,this);
	ravenlandright->setFPS(10);

	ravenlandleft = new animation;
	ravenlandleft->init("raven_land");
	ravenlandleft->setPlayFrame(7, 4, false, false, appearidle,this);
	ravenlandleft->setFPS(10);
	SOUNDMANAGER->play("±î¸¶±Í¼Ò¸®2", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
	_img = IMAGEMANAGER->findImage("raven_land");
	if (info.direction == E_LEFT) _motion = ravenlandleft;
	if (info.direction == E_RIGHT) _motion = ravenlandright;
	return S_OK;
}

void ravenAppear::update(enemyinfo & info)
{
	_pt = info.pt;
	if (isBurrowEnd == true) info.nextState = E_IDLE;
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void ravenAppear::appearidle(void * obj)
{
	ravenAppear*m = (ravenAppear*)obj;
	m->isBurrowEnd = true;

}
