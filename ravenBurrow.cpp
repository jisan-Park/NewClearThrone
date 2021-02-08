#include "stdafx.h"
#include "ravenBurrow.h"

HRESULT ravenBurrow::init(enemyinfo info)
{
	ravenliftright = new animation;
	ravenliftright->init("raven_lift");
	ravenliftright->setPlayFrame(0, 4, false, false, immune,this);
	ravenliftright->setFPS(10);

	ravenliftleft = new animation;
	ravenliftleft->init("raven_lift");
	ravenliftleft->setPlayFrame(9, 5, false, false, immune2,this);
	ravenliftleft->setFPS(10);

	ravenflyright = new animation;
	ravenflyright->init("raven_fly");
	ravenflyright->setPlayFrame(0, 4, false, true);
	ravenflyright->setFPS(10);

	ravenflyleft = new animation;
	ravenflyleft->init("raven_fly");
	ravenflyleft->setPlayFrame(9, 5, false, true);
	ravenflyleft->setFPS(10);
	SOUNDMANAGER->play("±î¸¶±Í¼Ò¸®1", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
	_img = IMAGEMANAGER->findImage("raven_lift");
	if (info.direction == E_LEFT) _motion = ravenliftleft;
	if (info.direction == E_RIGHT) _motion = ravenliftright;
	_motion->start();

	_pt = info.pt;

	return S_OK;
}

void ravenBurrow::update(enemyinfo & info)
{
	_pt = info.pt;


	if (!MAPMANAGER->isCollisionTile(info.pt, info.width, info.height)) {
		info.pt.x += cosf(info.moveAngle)* info.speed;
		info.pt.y += -sinf(info.moveAngle)* info.speed;
	}


	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void ravenBurrow::immune(void * obj)
{
	ravenBurrow*m = (ravenBurrow*)obj;
	m->setImage(IMAGEMANAGER->findImage("raven_fly"));
	m->setteMotion(m->ravenflyright);
	m->getMotion()->start();
}

void ravenBurrow::immune2(void * obj)
{
	ravenBurrow*m = (ravenBurrow*)obj;
	m->setImage(IMAGEMANAGER->findImage("raven_fly"));
	m->setteMotion(m->ravenflyleft);
	m->getMotion()->start();
}