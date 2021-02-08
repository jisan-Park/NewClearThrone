#include "stdafx.h"
#include "bigDog.h"

HRESULT bigDog::init(float x, float y)
{
	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 160;
	_info.height = 100;
	_info.hp = 25;
	_info.speed = _info.originSpeed = 0.5f;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;

	_info.state = E_IDLE;
	_info.nextState = E_IDLE;
	_info.noticeRange = 300;
	_info.nstate = UNNOTICED;
	_rndInterval = RND->getFromIntTo(70, 130);

	_enemyType = BIGDOG;
	_enState = new bigDogIdle;
	_enState->init(_info);
	return S_OK;
}

void bigDog::update()
{
	if (_info.hp > 0)
	{
		_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
		_enState->update(_info);
		_rndMoveCnt++;
		if (_info.state != E_DEAD)
		{
			collision();
			if (_info.hp <= 0) _info.nextState = E_DEAD;

			if (inRange() == true)
			{
				if (_info.nstate == UNNOTICED)
				{
					SOUNDMANAGER->play("ºòµ¶µîÀå", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
					_info.nstate = NOTICED;
				}
				_fireCnt++;
				if (_fireCnt % 5 == 0)
				{
					_info.aimAngle = 0;
					_info.nextState = E_FIRE;
					_fireCnt = 0;
				}
			}
		}
	}
	setState(_info.nextState);
}

void bigDog::render(HDC hdc)
{
	if (_info.hp > 0) _enState->render(hdc);
}

void bigDog::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:	_enState = new bigDogIdle;
		break;
	case E_FIRE:	_enState = new bigDogSpin;
		break;
	default:
		break;
	}
	_enState->init(_info);
}
