#include "stdafx.h"
#include "gator.h"


HRESULT gator::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 30;
	_info.height = 30;
	_info.hp = 40;
	_info.speed = _info.originSpeed = 3;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_enemyType = GATOR;

	_info.state = E_IDLE;
	_info.nextState = E_IDLE;
	_info.noticeRange = 300;
	_info.nstate = UNNOTICED;
	_rndInterval = RND->getFromIntTo(70, 130);

	_enState = new gatorIdle;
	_enState->init(_info);

	_weapon = new gatorGun;
	_weapon->init(_info.pt, NOWUSING);
	return S_OK;

}

void gator::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	collision();
	
	_rndMoveCnt++;
	if (_info.state != E_DEAD)
	{
		_weapon->update();
		_weapon->setPt(_info.pt);
		_weapon->setAngle(_info.aimAngle);
		if (_info.hp <= 0) _info.nextState = E_DEAD;

		if (inRange() == true)
		{
			_info.aimAngle = EtoPAngle();
			_info.nstate == NOTICED;
			if (_info.state == E_IDLE) _info.nextState == E_WALK;
			_info.moveAngle = getAngle(_info.pt, MAPMANAGER->enemyMove(_info.pt));
			if (_info.pt.x == MAPMANAGER->enemyMove(_info.pt).x && _info.pt.y == MAPMANAGER->enemyMove(_info.pt).y) {
				_info.nextState = E_IDLE;
			}
			_fireCnt++;
			if (_fireCnt % 60 == 0 && MAPMANAGER->isStraight(PLAYERMANAGER->getPlayer()->getPt(), _info.pt))
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

void gator::render(HDC hdc)
{
	_enState->render(hdc);
	_weapon->render(hdc);
}

void gator::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new gatorIdle;
		break;
	case E_WALK:	_enState = new gatorWalk;
		break;
	case E_DEAD:	_enState = new gatorDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}


