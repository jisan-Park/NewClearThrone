#include "stdafx.h"
#include "bigRat.h"

HRESULT bigRat::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 60;
	_info.height = 60;
	_info.hp = 40;
	_info.speed = 3;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = BIGRAT;
	_enState = new bigRatIdle;
	_enState->init(_info);

	return S_OK;
}

void bigRat::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
}

void bigRat::render(HDC hdc)
{
	_enState->render(hdc);
}

void bigRat::setState(ENEMYSTATE state)
{
	if (_info.state == state)return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:		_enState = new bigRatIdle;
		break;
	case E_WALK:		_enState = new bigRatWalk;
		break;
	case E_DEAD:		_enState = new bigRatDead;
		break;
	case E_FIRE:		_enState = new bigRatFire;
		break;
	case E_ATTACK:		_enState = new bigRatAttack;
		break;
	default:
		break;
	}
	_enState->init(_info);
}
