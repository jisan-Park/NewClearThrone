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
	_info.state = E_IDLE;
	_info.nextState = E_IDLE;
	_info.nstate = UNNOTICED;
	_info.noticeRange = 400;
	
	_enemyType = BIGBANDIT;
	_enState = new bigBanditIdle;
	_enState->init(_info);
	_weapon = new bigBanditGun;
	_weapon->init(_info.pt, NOWUSING);
	return S_OK;
}

void bigBandit::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);

	_rndMoveCnt++;

	if (_info.state != E_DEAD)
	{
		_weapon->update();
		_weapon->setPt(_info.pt);
		_weapon->setAngle(_info.aimAngle);
		if (_info.hp <= 0) _info.nextState = E_DEAD;

		if (inRange())
		{
			_info.aimAngle = EtoPAngleRnd();
			_info.nstate = NOTICED;
			if (_info.state == E_IDLE)
				_info.nextState == E_WALK;
			_info.moveAngle = getAngle(_info.pt, MAPMANAGER->enemyMove(_info.pt));

			if (_info.pt.x == MAPMANAGER->enemyMove(_info.pt).x && _info.pt.y == MAPMANAGER->enemyMove(_info.pt).y) {
				_info.nextState = E_IDLE;
			}
			_fireCnt++;
			if (_fireCnt % 10 == 0 && MAPMANAGER->isStraight(PLAYERMANAGER->getPlayer()->getPt(), _info.pt))
			{
				_weapon->fire();
				_fireCnt = 0;
			}
		}

		else _info.aimAngle = _info.moveAngle;

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

	}

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

