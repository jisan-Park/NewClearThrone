#include "stdafx.h"
#include "bigDog.h"

HRESULT bigDog::init(float x, float y)
{//158/100
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 160;
	_info.height = 100;
	_info.hp = 60;
	_info.speed = _info.originSpeed = 10;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = BIGDOG;
	_enState = new bigDogIdle;
	_enState->init(_info);
	return S_OK;
}

void bigDog::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
	collision();
	if (_info.hp <= 0) _info.nextState = E_DEAD;
}

void bigDog::render(HDC hdc)
{
	_enState->render(hdc);
}

void bigDog::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new bigDogIdle;
		break;
	case E_FIRE:	_enState = new bigDogSpin;
		break;
	case E_DEAD:	// 죽을때 어떻게 할지 정해야함
		break;
	default:
		break;
	}
	_enState->init(_info);
}
