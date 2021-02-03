#include "stdafx.h"
#include "gator.h"


HRESULT gator::init(float x, float y)
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
	_enemyType = GATOR;
	_enState = new gatorIdle;
	_enState->init(_info);
	return S_OK;

}

void gator::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
}

void gator::render(HDC hdc)
{
	_enState->render(hdc);
}

void gator::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new gatorIdle;
		break;
	case E_WALK:	_enState = new gatorWalk;
		break;
	case E_DEAD:	_enState = new gatorDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}


