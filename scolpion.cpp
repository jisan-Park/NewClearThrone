#include "stdafx.h"
#include "scolpion.h"

HRESULT scolpion::init(float x, float y)
{//6565
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 65;
	_info.height = 65;
	_info.hp = 60;
	_info.speed = 10;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = SCOLPION;
	_enState = new scolpionIdle;
	_enState->init(_info);
	return S_OK;
}

void scolpion::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
}

void scolpion::render(HDC hdc)
{
	_enState->render(hdc);
}

void scolpion::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new scolpionIdle;
		break;
	case E_WALK:	_enState = new scolpionWalk;
		break;
	case E_FIRE:	_enState = new scolpionFire;
		break;
	case E_DEAD:	_enState = new scolpionDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}
