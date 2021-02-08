#include "stdafx.h"
#include "assassin.h"

HRESULT assassin::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 30;
	_info.height = 30;
	_info.hp = 20;
	_info.speed = _info.originSpeed = 5;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_info.state = E_IDLE;
	_info.nextState = E_IDLE;
	_info.noticeRange = 300;
	_info.nstate = UNNOTICED;
	_rndInterval = RND->getFromIntTo(70, 130);
	_enemyType = ASSASSIN;
	_enState = new assassinIdle;
	_enState->init(_info);
	_weapon = new bbaRU;
	_weapon->init(_info.pt, NOWUSING);

	return S_OK;
}

void assassin::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	setState(_info.nextState);
	
	if (_info.state != E_DEAD)
	{
		collision();
		_weapon->update();
		_weapon->setPt(_info.pt);
		_weapon->setAngle(_info.aimAngle);

		if (_info.hp <= 0) _info.nextState = E_DEAD;

		if (inRange() == true)
		{
			/*if (_info.state == E_IDLE) _info.nextState = E_WALK;
			_info.moveAngle = getAngle(_info.pt, MAPMANAGER->enemyMove(_info.pt));*/
			
			/*_fireCnt++;
			if (_fireCnt % 30 == 0 && MAPMANAGER->isStraight(PLAYERMANAGER->getPlayer()->getPt(), _info.pt))
			{
				_weapon->fire();
				_fireCnt = 0;
			}*/
		}
		else _info.aimAngle = _info.moveAngle;
		
	}
}

void assassin::render(HDC hdc)
{
	_enState->render(hdc);
	_weapon->render(hdc);
}

void assassin::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new assassinIdle;
		break;
	case E_WALK:	_enState = new assassinWalk;
	break;
	case E_DEAD:	_enState = new assassinDead;
		break;
	default:
		break;
	}
	_enState->init(_info);
}

void assassin::meleeattack()
{
	
}

