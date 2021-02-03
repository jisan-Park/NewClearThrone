#include "stdafx.h"
#include "greenFrog.h"

HRESULT greenFrog::init(float x, float y)
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
	_enemyType = GREENFROG;
	_enState = new greenFrogIdle;
	_enState->init(_info);
	return S_OK;
}

void greenFrog::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
}

void greenFrog::render(HDC hdc)
{
	_enState->render(hdc);
}

void greenFrog::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new greenFrogIdle;
		break;
	case E_WALK:	_enState = new greenFrogWalk;
		break;
	case E_DEAD:	_enState = new greenFrogDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}


