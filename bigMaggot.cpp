#include "stdafx.h"
#include "bigMaggot.h"

HRESULT bigMaggot::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 30;
	_info.height = 30;
	_info.hp = 20;
	_info.speed = 2;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_info.state = E_IDLE;
	_info.nextState = E_IDLE;
	_info.noticeRange = 300;
	_info.nstate = UNNOTICED;
	_rndInterval = RND->getFromIntTo(70, 130);
	_enemyType = BIGMAGGOT;
	_enState = new bigMaggotIdle;
	_enState->init(_info);
	return S_OK;
}

void bigMaggot::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	collision();
	_rndMoveCnt++;
	if (inRange() == true)
	{
		_info.nstate = NOTICED;
		_info.moveAngle = getAngle(_info.pt, MAPMANAGER->enemyMove(_info.pt));
	}


	if (_rndMoveCnt % _rndInterval == 0)
	{
		if (_info.speed < 2)
		{
			if (_info.nstate == UNNOTICED)_info.moveAngle = RND->getFloat(PI2);
			_info.speed = 2;
			_rndInterval = RND->getFromIntTo(70, 130);
			_rndMoveCnt = 0;
		}
		else if (_info.speed <= 2)
		{
			if (_info.nstate == UNNOTICED)_info.moveAngle = RND->getFloat(PI2);
			_info.speed = 1;
			_rndInterval = RND->getFromIntTo(70, 130);
			_rndMoveCnt = 0;
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

