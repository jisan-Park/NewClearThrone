#include "stdafx.h"
#include "bigMaggot.h"

HRESULT bigMaggot::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 60;
	_info.height = 35;
	_info.hp = 60;
	_info.speed = 1;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_info.noticeRange = 500;
	_info.nstate = UNNOTICED;
	_enemyType = BIGMAGGOT;
	_enState = new bigMaggotIdle;
	_enState->init(_info);
	return S_OK;
}

void bigMaggot::update()
{
	collision();
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	_rndMoveCnt++;
	if (_rndMoveCnt % 70 == 0)
	{
		if (_info.state == E_IDLE)
		{
			_info.moveAngle = RND->getFloat(PI2);
			_info.nextState = E_WALK;
			_rndMoveCnt = 0;
		}
		if (_info.state == E_WALK)
		{
			_info.nextState = E_IDLE;
			_rndMoveCnt == 0;
		}
	}
	setState(_info.nextState);

}

void bigMaggot::render(HDC hdc)
{
	_enState->render(hdc);
}

void bigMaggot::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new bigMaggotIdle;
		break;
	case E_DEAD:	_enState = new bigMaggotDead;
		break;
	case E_IMMUNE:	_enState = new bigMaggotBurrow;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

