#include "stdafx.h"
#include "maggot.h"

HRESULT maggot::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 28;
	_info.height = 14;
	_info.hp = 1;
	_info.speed = 10;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = MAGGOT;
	_enState = new maggotIdle;
	_enState->init(_info);
	return S_OK;
}

void maggot::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
}

void maggot::render(HDC hdc)
{
	_enState->render(hdc);
}

void maggot::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new maggotIdle;
		break;
	case E_DEAD:	_enState = new maggotDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}


