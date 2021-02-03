#include "stdafx.h"
#include "rat.h"

HRESULT rat::init(float x, float y)
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
	_enemyType = RAT;
	_enState = new ratIdle;
	_enState->init(_info);
	return S_OK;

}

void rat::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
}

void rat::render(HDC hdc)
{
	_enState->render(hdc);
}

void rat::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new ratIdle;
		break;
	case E_WALK:	_enState = new ratWalk;
		break;
	case E_DEAD:	_enState = new ratDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

