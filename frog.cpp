#include "stdafx.h"
#include "frog.h"

HRESULT frog::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 30;
	_info.height = 30;
	_info.hp = 40;
	_info.speed = 10;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = FROG;
	_enState = new frogIdle;
	_enState->init(_info);
	return S_OK;
}

void frog::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
}

void frog::render(HDC hdc)
{
	_enState->render(hdc);
}

void frog::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new frogIdle;
		break;
	case E_WALK:	_enState = new frogWalk;
		break;
	case E_DEAD:	_enState = new frogDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

