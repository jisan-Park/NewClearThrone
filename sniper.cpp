#include "stdafx.h"
#include "sniper.h"

HRESULT sniper::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 30;
	_info.height = 30;
	_info.hp = 20;
	_info.speed = _info.originSpeed = 5;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = SNIPER;
	_enState = new sniperIdle;
	_enState->init(_info);
	return S_OK;
}

void sniper::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
}

void sniper::render(HDC hdc)
{
	_enState->render(hdc);
}

void sniper::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new sniperIdle;
		break;
	case E_WALK:
		break;
	case E_DEAD:
		break;
	default:
		break;
	}
	_enState->init(_info);
}
