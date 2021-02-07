#include "stdafx.h"
#include "frogDead.h"


HRESULT frogDead::init(enemyinfo info)
{
	frogdeadright = new animation;
	frogdeadright->init("frog_dead");
	frogdeadright->setPlayFrame(0, 7, false, false);
	frogdeadright->setFPS(10);

	frogdeadleft = new animation;
	frogdeadleft->init("frog_dead");
	frogdeadleft->setPlayFrame(15, 8, false, false);
	frogdeadleft->setFPS(10);

	_img = IMAGEMANAGER->findImage("frog_dead");
	if (info.direction == E_LEFT) _motion = frogdeadleft;
	if (info.direction == E_RIGHT)_motion = frogdeadright;
	_motion->start();
	_pt = info.pt;
	deadEffect();

	return S_OK;
}

void frogDead::update(enemyinfo & info)
{
	_pt = info.pt;
	
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void frogDead::deadEffect()
{
	for (int i = 0; i < 35; i++)
	{
		BULLETMANAGER->EnemyFire(E_ANGLE16_2, _pt, 5, (PI / 9)*i, 5);
	}
}