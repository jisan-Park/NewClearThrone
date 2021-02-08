#include "stdafx.h"
#include "salamander.h"


HRESULT salamander::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 65;
	_info.height = 65;
	_info.hp = 8;
	_info.speed = _info.originSpeed = 3;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType =SALAMADER;

	_info.state = E_IDLE;
	_info.nextState = E_IDLE;
	_info.noticeRange = 400;
	_info.nstate = UNNOTICED;
	_rndInterval = RND->getFromIntTo(70, 130);

	_enState = new salamanderIdle;
	_enState->init(_info);
	return S_OK;
}

void salamander::update()
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
			_fireCnt++;
			if (_fireCnt % 50 == 0)
			{
				_info.aimAngle = EtoPAngle();
				_info.nextState = E_FIRE;
				_fireCnt = 0;
			}
		}
		if (_info.nstate == UNNOTICED)
		{
			if (_rndMoveCnt % _rndInterval == 0)
			{
				if (_info.state == E_IDLE)
				{
					_info.nextState = E_WALK;
					_info.moveAngle = getAngle(_info.pt, MAPMANAGER->enemyMove(_info.pt));
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
	}
	setState(_info.nextState);
}

void salamander::render(HDC hdc)
{
	_enState->render(hdc);
}

void salamander::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:_enState = new salamanderIdle;
		break;
	case E_WALK:_enState = new salamanderWalk;
		break;
	case E_FIRE:_enState = new salamanderFire;
		break;
	case E_DEAD:_enState = new salamanderDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

