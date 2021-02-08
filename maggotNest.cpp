#include "stdafx.h"
#include "maggotNest.h"

HRESULT maggotNest::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 60;
	_info.height = 35;
	_info.hp = 60;
	_info.speed = _info.originSpeed = 0;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = MAGGOTNEST;
	_enState = new maggotNestIdle;
	_enState->init(_info);
	return S_OK;
}

void maggotNest::update()
{
	_enState->update(_info);
	setState(_info.nextState);
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);

	if (_info.hp <= 0) _info.nextState = E_DEAD;
	if (_info.state != E_DEAD)
	{
		collision();
	}
}

void maggotNest::render(HDC hdc)
{
	_enState->render(hdc);
}

void maggotNest::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new maggotNestIdle;
		break;
	case E_DEAD:	_enState = new maggotNestDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

