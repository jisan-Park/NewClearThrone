#include "stdafx.h"
#include "raven.h"

HRESULT raven::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 30;
	_info.height = 30;
	_info.hp = 20;
	_info.speed = 5;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = RAVEN;
	_enState = new ravenIdle;
	_enState->init(_info);
	return S_OK;
}

void raven::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
}

void raven::render(HDC hdc)
{
	_enState->render(hdc);
}

void raven::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new ravenIdle;
		break;
	case E_WALK:	_enState = new ravenWalk;
		break;
	case E_DEAD:	_enState = new ravenDead;
		break;
	case E_IMMUNE:	_enState = new ravenFly;
		break;
	default:
		break;
	}
	_enState->init(_info);
}
//
//void raven::setAnimation()
//{
//	ravendeadright = new animation;
//	ravendeadright->init("raven_dead");
//	ravendeadright->setPlayFrame(0, 5, false, false);
//	ravendeadright->setFPS(10);
//
//	ravendeadleft = new animation;
//	ravendeadleft->init("raven_dead");
//	ravendeadleft->setPlayFrame(11, 6, false, false);
//	ravendeadleft->setFPS(10);
//
//
//
//	ravenflyright = new animation;
//	ravenflyright->init("raven_fly");
//	ravenflyright->setPlayFrame(0, 4, false, true);
//	ravenflyright->setFPS(10);
//
//	ravenflyleft = new animation;
//	ravenflyleft->init("raven_fly");
//	ravenflyleft->setPlayFrame(9, 5, false, true);
//	ravenflyleft->setFPS(10);
//
//
//
//
//
//
//	ravenhurtright = new animation;
//	ravenhurtright->init("raven_hurt");
//	ravenhurtright->setPlayFrame(0, 2, false, false);
//	ravenhurtright->setFPS(10);
//
//	ravenhurtleft = new animation;
//	ravenhurtleft->init("raven_hurt");
//	ravenhurtleft->setPlayFrame(5, 3, false, false);
//	ravenhurtleft->setFPS(10);
//
//
//
//	ravenidleright = new animation;
//	ravenidleright->init("raven_idle");
//	ravenidleright->setPlayFrame(0, 8, false, true);
//	ravenidleright->setFPS(10);
//
//	ravenidleleft = new animation;
//	ravenidleleft->init("raven_idle");
//	ravenidleleft->setPlayFrame(15, 9, false, true);
//	ravenidleleft->setFPS(10);
//
//
//
//	ravenlandright = new animation;
//	ravenlandright->init("raven_land");
//	ravenlandright->setPlayFrame(0, 3, false, false);
//	ravenlandright->setFPS(10);
//
//	ravenlandleft = new animation;
//	ravenlandleft->init("raven_land");
//	ravenlandleft->setPlayFrame(7, 4, false, false);
//	ravenlandleft->setFPS(10);
//
//
//
//	ravenliftright = new animation;
//	ravenliftright->init("raven_lift");
//	ravenliftright->setPlayFrame(0, 4, false, false);
//	ravenliftright->setFPS(10);
//
//	ravenliftleft = new animation;
//	ravenliftleft->init("raven_lift");
//	ravenliftleft->setPlayFrame(9, 5, false, false);
//	ravenliftleft->setFPS(10);
//
//
//
//	ravenwalkright = new animation;
//	ravenwalkright->init("raven_walk");
//	ravenwalkright->setPlayFrame(0, 5, false, true);
//	ravenwalkright->setFPS(10);
//
//	ravenwalkleft = new animation;
//	ravenwalkleft->init("raven_walk");
//	ravenwalkleft->setPlayFrame(11, 6, false, true);
//	ravenwalkleft->setFPS(10);
//}
