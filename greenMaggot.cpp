#include "stdafx.h"
#include "greenMaggot.h"

HRESULT greenMaggot::init(float x, float y)
{
	//28,14
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 28;
	_info.height = 14;
	_info.hp = 2;
	_info.speed = _info.originSpeed = 2;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_info.state = E_IDLE;
	_info.nextState = E_IDLE;
	_rndInterval = RND->getFromIntTo(70, 130);
	_info.nstate = UNNOTICED;
	_enemyType = GREENMAGGOT;
	_info.noticeRange = 500;
	_enState = new greenMaggotIdle;
	_enState->init(_info);
	return S_OK;
}

void greenMaggot::update()
{
	collision();
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);


	if (_info.hp <= 0) _info.nextState = E_DEAD;
	if (_info.state != E_DEAD)
	{
		_rndMoveCnt++;

		if (inRange() == true)
		{
			_info.nstate = NOTICED;
			_info.moveAngle = getAngle(_info.pt, MAPMANAGER->enemyMove(_info.pt));
		}


		if (_rndMoveCnt % _rndInterval == 0)
		{
			if (_info.speed < 3)
			{
				if (_info.nstate == UNNOTICED)_info.moveAngle = getAngle(_info.pt, MAPMANAGER->enemyRandomMove(_info.pt));
				_info.speed = 3;
				_rndInterval = RND->getFromIntTo(70, 130);
				_rndMoveCnt = 0;
			}
			else if (_info.speed >= 3)
			{
				if (_info.nstate == UNNOTICED)_info.moveAngle = getAngle(_info.pt, MAPMANAGER->enemyRandomMove(_info.pt));
				_info.speed = 2;
				_rndInterval = RND->getFromIntTo(70, 130);
				_rndMoveCnt = 0;
			}
		}
	}

	setState(_info.nextState);
}

void greenMaggot::render(HDC hdc)
{
	_enState->render(hdc);
}

void greenMaggot::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new greenMaggotIdle;
		break;
	case E_DEAD:	_enState = new greenMaggotDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

