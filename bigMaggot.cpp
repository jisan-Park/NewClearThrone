#include "stdafx.h"
#include "bigMaggot.h"

HRESULT bigMaggot::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 30;
	_info.height = 30;
	_info.hp = 5;
	_info.speed = _info.originSpeed = 2;
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

	/////
	_rndMoveCnt = 50;
	return S_OK;
}

void bigMaggot::update()
{
	//if (_info.state == E_DEAD) return;
	_enState->update(_info);
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);

	if (_info.hp <= 0) _info.nextState = E_DEAD;
	if (_info.state != E_DEAD)
	{
		collision();

		_rndMoveCnt++;
		if (_rndMoveCnt % 30 == 0)
		{
			int rnd;
			rnd = RND->getFromIntTo(1, 10);
			if (rnd > 2)
			{
				if (_info.state != E_BURROW)
					_info.nextState = E_IDLE;

			}
			else
			{
				if (inRange() == true)
				{
					_info.nstate = NOTICED;
					_info.moveAngle = getAngle(_info.pt, MAPMANAGER->enemyMove(_info.pt));
					if (_info.state != E_APPEAR && 128 < getDistance(_info.pt, PLAYERMANAGER->getPlayer()->getPt()))
					{
						_info.nextState = E_BURROW;

					}
				}
			}
			_rndMoveCnt = 0;
		}

		_info.moveAngle = getAngle(_info.pt, MAPMANAGER->enemyMove(_info.pt));

		if (_info.state == E_BURROW)
		{
			int index_x = 0;
			int index_y = 0;

			int next_x = 0;
			int next_y = 0;

			index_x = _info.pt.x / 64;
			index_y = _info.pt.y / 64;

			next_x = PLAYERMANAGER->getPlayer()->getPt().x / 64;
			next_y = PLAYERMANAGER->getPlayer()->getPt().y / 64;
			if (abs(index_x - next_x) <= 1 && abs(index_y - next_y) <= 1)
			{
				_info.nextState = E_APPEAR;
			}
		}

		if (_rndMoveCnt % _rndInterval == 0)
		{
			if (_info.speed < 2)
			{
				if (_info.nstate == UNNOTICED)_info.moveAngle = RND->getFloat(PI2);
				_info.speed = _info.originSpeed = 2;
				_rndInterval = RND->getFromIntTo(70, 130);
				_rndMoveCnt = 0;
			}
			else if (_info.speed <= 2)
			{
				if (_info.nstate == UNNOTICED)_info.moveAngle = RND->getFloat(PI2);
				_info.speed = _info.originSpeed = 1;
				_rndInterval = RND->getFromIntTo(70, 130);
				_rndMoveCnt = 0;
			}
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
	case E_BURROW:	_enState = new bigMaggotBurrow;
		break;
	case E_APPEAR:	_enState = new bigMaggotAppear;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

