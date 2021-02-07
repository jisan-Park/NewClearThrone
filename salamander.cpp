#include "stdafx.h"
#include "salamander.h"


HRESULT salamander::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 65;
	_info.height = 65;
	_info.hp = 60;
	_info.speed = _info.originSpeed = 10;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType =SALAMADER;
	_enState = new salamanderIdle;
	_enState->init(_info);
	return S_OK;
}

void salamander::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
	collision();
	if (_info.hp <= 0) _info.nextState = E_DEAD;
}

void salamander::render(HDC hdc)
{
	_enState->render(hdc);
}

void salamander::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:_enState = new salamanderIdle;
		break;
	case E_WALK:_enState = new salamanderWalk;
		break;
	case E_FIRE:_enState = new salamanderFire;
		break;
	case E_DEAD:_enState = new salamanderDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

void salamander::setAnimation()
{
	salamanderfireright = new animation;
	salamanderfireright->init("salamander_fire");
	salamanderfireright->setPlayFrame(0, 7, false, false);
	salamanderfireright->setFPS(10);

	salamanderfireleft = new animation;
	salamanderfireleft->init("salamander_fire");
	salamanderfireleft->setPlayFrame(15, 8, false, false);
	salamanderfireleft->setFPS(10);



	salamanderdeadright = new animation;
	salamanderdeadright->init("salamander_dead");
	salamanderdeadright->setPlayFrame(0, 1, false, false);
	salamanderdeadright->setFPS(10);

	salamanderdeadleft = new animation;
	salamanderdeadleft->init("salamander_dead");
	salamanderdeadleft->setPlayFrame(3, 2, false, false);
	salamanderdeadleft->setFPS(10);



	salamanderhurtright = new animation;
	salamanderhurtright->init("salamander_hurt");
	salamanderhurtright->setPlayFrame(0, 2, false, false);
	salamanderhurtright->setFPS(10);

	salamanderhurtleft = new animation;
	salamanderhurtleft->init("salamander_hurt");
	salamanderhurtleft->setPlayFrame(5, 3, false, false);
	salamanderhurtleft->setFPS(10);



	salamanderidleright = new animation;
	salamanderidleright->init("salamander_idle");
	salamanderidleright->setPlayFrame(0, 6, false, true);
	salamanderidleright->setFPS(10);

	salamanderidleleft = new animation;
	salamanderidleleft->init("salamander_idle");
	salamanderidleleft->setPlayFrame(13, 7, false, true);
	salamanderidleleft->setFPS(10);



	salamanderwalkright = new animation;
	salamanderwalkright->init("salamander_walk");
	salamanderwalkright->setPlayFrame(0, 7, false, true);
	salamanderwalkright->setFPS(10);

	salamanderwalkleft = new animation;
	salamanderwalkleft->init("salamander_walk");
	salamanderwalkleft->setPlayFrame(15, 8, false, true);
	salamanderwalkleft->setFPS(10);



}
