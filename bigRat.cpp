#include "stdafx.h"
#include "bigRat.h"

HRESULT bigRat::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 60;
	_info.height = 60;
	_info.hp = 10;
	_info.speed = _info.originSpeed = 3;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = BIGRAT;
	_enState = new bigRatIdle;
	_enState->init(_info);

	_info.nextState = E_IDLE;
	_info.noticeRange = 300;
	_info.nstate = UNNOTICED;
	_rndInterval = RND->getFromIntTo(70, 130);

	return S_OK;
}

void bigRat::update()
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
		}

		if (_info.nstate == UNNOTICED)
		{
			if (_rndMoveCnt % _rndInterval == 0)
			{
				if (_info.state == E_IDLE)
				{
					_info.nextState = E_WALK;
					_info.moveAngle = getAngle(_info.pt, MAPMANAGER->enemyRandomMove(_info.pt));
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

void bigRat::render(HDC hdc)
{
	_enState->render(hdc);
}

void bigRat::setState(ENEMYSTATE state)
{
	if (_info.state == state)return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:		_enState = new bigRatIdle;
		break;
	case E_WALK:		_enState = new bigRatWalk;
		break;
	case E_DEAD:		_enState = new bigRatDead;
		break;
	case E_FIRE:		_enState = new bigRatFire;
		break;
	case E_ATTACK:		_enState = new bigRatAttack;
		break;
	default:
		break;
	}
	_enState->init(_info);
}
