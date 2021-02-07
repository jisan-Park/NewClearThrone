#include "stdafx.h"
#include "frog.h"

HRESULT frog::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 30;
	_info.height = 30;
	_info.hp = 40;
	_info.speed = _info.originSpeed = 10;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = FROG;

	_info.state = E_IDLE;
	_info.nextState = E_IDLE;
	_info.noticeRange = 400;
	_info.nstate = UNNOTICED;
	_rndInterval = RND->getFromIntTo(70, 130);

	_enState = new frogIdle;
	_enState->init(_info);
	return S_OK;
}

void frog::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	collision();
	_rndMoveCnt++;
	if (_info.hp <= 0) _info.nextState = E_DEAD;
	if (_info.state != E_DEAD)
	{
		if (inRange() == true)
		{
			_info.nstate == NOTICED;
			_info.moveAngle = getAngle(_info.pt, MAPMANAGER->enemyMove(_info.pt));

			_info.nextState == E_WALK;

			if (64 > getDistance(_info.pt, PLAYERMANAGER->getPlayer()->getPt()))
			{
				_info.nextState = E_IDLE;
			}

		}

		if (_info.nstate == UNNOTICED)
		{
			if (_rndMoveCnt % _rndInterval == 0)
			{
				if (_info.state == E_IDLE)
				{
					_info.nextState = E_WALK;
					_info.moveAngle = RND->getFloat(PI2);
					_rndInterval = RND->getFromIntTo(70, 130);
					_rndMoveCnt = 0;
				}
				if (_info.state == E_WALK)
				{
					_info.nextState = E_IDLE;
					_rndInterval = RND->getFromIntTo(70, 130);
					_rndMoveCnt == 0;
				}
			}
		}
		setState(_info.nextState);
	}
}

void frog::render(HDC hdc)
{
	_enState->render(hdc);
}

void frog::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new frogIdle;
		break;
	case E_WALK:	_enState = new frogWalk;
		break;
	case E_DEAD:	_enState = new frogDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

