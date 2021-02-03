#include "stdafx.h"
#include "greenRat.h"

HRESULT greenRat::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 30;
	_info.height = 30;
	_info.hp = 15;
	_info.speed = 15;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = GREENRAT;
	_enState = new greenRatIdle;
	_enState->init(_info);
	return S_OK;
}

void greenRat::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
}

void greenRat::render(HDC hdc)
{
	_enState->render(hdc);
}

void greenRat::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new greenRatIdle;
		break;
	case E_WALK:	_enState = new greenRatWalk;
		break;
	case E_DEAD:	_enState = new greenRatDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

