#include "stdafx.h"
#include "bigBandit.h"

HRESULT bigBandit::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 60;
	_info.height = 60;
	_info.hp = 100;
	_info.speed = 10;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = BIGBANDIT;
	_enState = new bigBanditIdle;
	_enState->init(_info);

	return S_OK;
}

void bigBandit::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
}

void bigBandit::render(HDC hdc)
{
	_enState->render(hdc);
}

void bigBandit::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new bigBanditIdle;
		break;
	case E_WALK:	_enState = new bigBanditWalk;
		break;
	case E_FIRE:	_enState = new bigBanditFire;
		break;
	case E_DEAD:	_enState = new bigBanditDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

