#include "stdafx.h"
#include "assassin.h"

HRESULT assassin::init(float x, float y)
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
	_enemyType = ASSASSIN;

	_info.state = E_IDLE;
	_info.nextState = E_IDLE;
	_info.noticeRange = 300;
	_info.nstate = UNNOTICED;
	_rndInterval = RND->getFromIntTo(70, 130);

	_enState = new assassinIdle;
	_enState->init(_info);

	return S_OK;
}

void assassin::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
	collision();
	if (_info.hp <= 0) _info.nextState = E_DEAD;
}

void assassin::render(HDC hdc)
{
	_enState->render(hdc);
}

void assassin::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new assassinIdle;
		break;
	case E_WALK:	_enState = new assassinWalk;
	break;
	case E_DEAD:	_enState = new assassinDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

