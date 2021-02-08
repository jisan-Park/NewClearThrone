#include "stdafx.h"
#include "greenFrog.h"

HRESULT greenFrog::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 30;
	_info.height = 30;
	_info.hp = 10;
	_info.speed = _info.originSpeed = 5;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = GREENFROG;

	_info.state = E_IDLE;
	_info.nextState = E_IDLE;
	_info.noticeRange = 400;
	_info.nstate = UNNOTICED;
	_rndInterval = RND->getFromIntTo(70, 130);

	_enState = new greenFrogIdle;
	_enState->init(_info);
	return S_OK;
}

void greenFrog::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	collision();
	_rndMoveCnt++;
	if (_info.hp <= 0) _info.nextState = E_DEAD;
	if (_info.state != E_DEAD)
	{
		_fireCnt++;
		if (_fireCnt % 100 == 0)
		{
			for (int i = 0; i < 17; i++)
			{
				BULLETMANAGER->EnemyFire(E_ANGLE16_2, _info.pt, 3, (PI / 9)*i, 5);

			}

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
			setState(_info.nextState);
		}
	}
}

void greenFrog::render(HDC hdc)
{
	_enState->render(hdc);
}

void greenFrog::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new greenFrogIdle;
		break;
	case E_WALK:	_enState = new greenFrogWalk;
		break;
	case E_DEAD:	_enState = new greenFrogDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}


