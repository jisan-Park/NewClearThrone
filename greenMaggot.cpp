#include "stdafx.h"
#include "greenMaggot.h"

HRESULT greenMaggot::init(float x, float y)
{
	//28,14
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 28;
	_info.height = 14;
	_info.hp = 1;
	_info.speed = 10;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = GREENMAGGOT;
	_enState = new greenMaggotIdle;
	_enState->init(_info);
	return S_OK;
}

void greenMaggot::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
}

void greenMaggot::render(HDC hdc)
{
	_enState->render(hdc);
}

void greenMaggot::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new greenMaggotIdle;
		break;
	case E_DEAD:	_enState = new greenMaggotDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

