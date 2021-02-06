#include "stdafx.h"
#include "bigMaggotBurrow.h"

HRESULT bigMaggotBurrow::init(enemyinfo info)
{

	bigmaggotburrowright = new animation;
	bigmaggotburrowright->init("bigmaggot_burrow");
	bigmaggotburrowright->setPlayFrame(0, 11, false, false);
	bigmaggotburrowright->setFPS(10);

	bigmaggotburrowleft = new animation;
	bigmaggotburrowleft->init("bigmaggot_burrow");
	bigmaggotburrowleft->setPlayFrame(23, 12, false, false);
	bigmaggotburrowleft->setFPS(10);

	bigmaggotinvisible = new animation;
	bigmaggotinvisible->init("bigmaggot_burrow");
	bigmaggotinvisible->setPlayFrame(11, 12, false, true);
	bigmaggotinvisible->setFPS(10);

	_img = IMAGEMANAGER->findImage("bigmaggot_burrow");
	if (info.direction == E_LEFT) _motion = bigmaggotburrowleft;
	if (info.direction == E_RIGHT) _motion = bigmaggotburrowright;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void bigMaggotBurrow::update(enemyinfo & info)
{
	_pt = info.pt;

	info.pt.x += cosf(info.moveAngle)* info.speed;
	info.pt.y += -sinf(info.moveAngle)* info.speed;
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void bigMaggotBurrow::immune(void * obj)
{
	bigMaggotBurrow*m = (bigMaggotBurrow*)obj;
	m->setImage(IMAGEMANAGER->findImage("bigmaggot_burrow"));
	m->setteMotion(m->bigmaggotinvisible);
	m->getMotion()->start();
}
