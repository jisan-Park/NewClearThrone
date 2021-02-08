#include "stdafx.h"
#include "banditDead.h"
#include "bandit.h"

HRESULT banditDead::init(enemyinfo info)
{
	banditdeadright = new animation;
	banditdeadright->init("bandit_dead");
	banditdeadright->setPlayFrame(0, 6, false, false);
	banditdeadright->setFPS(10);

	banditdeadleft = new animation;
	banditdeadleft->init("bandit_dead");
	banditdeadleft->setPlayFrame(12, 6, false, false);
	banditdeadleft->setFPS(10);
	_img = IMAGEMANAGER->findImage("bandit_dead");
	if (info.direction == E_LEFT) _motion = banditdeadleft;
	if (info.direction == E_RIGHT)_motion = banditdeadright;
	_motion->start();
	SOUNDMANAGER->play("¿¡³Ê¹ÌÈý1", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
	return S_OK;
}

void banditDead::update(enemyinfo &info)
{
	_pt = info.pt;
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
