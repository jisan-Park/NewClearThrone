#include "stdafx.h"
#include "bandit.h"


HRESULT bandit::init(float x, float y)
{

	_info.pt.x = x;
	_info.pt.y = y;
	_info.width = 30;
	_info.height = 30;
	_info.hp = 20;
	_info.speed = 2;
	_info.moveAngle = 0;
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_info.direction = E_RIGHT;
	_info.state = E_IDLE;
	_info.noticeRange = 500;
	_info.nstate = UNNOTICED;
	_enemyType = BANDIT;
	_enState = new banditIdle;
	_enState->init(_info);
	return S_OK;
}

void bandit::update()
{
	_info.rc = RectMakeCenter(_info.pt.x, _info.pt.y, _info.width, _info.height);
	_enState->update(_info);
	collision();
	_rndMoveCnt++;
	if (_rndMoveCnt % 70 == 0)
	{
		if (_info.state == E_IDLE)
		{
			_info.moveAngle = RND->getFloat(PI2);
			_info.nextState = E_WALK;
			_rndMoveCnt = 0;
		}
		if (_info.state == E_WALK)
		{
			_info.nextState = E_IDLE;
			_rndMoveCnt == 0;
		}
	}
	//if (inRange() == true)
	//{
	//	_info.nextState = E_WALK;
	//	_info.moveAngle = EtoPAngle();
	//}
	//if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
	//	_info.direction = E_LEFT;
	//	_info.nextState = E_WALK;
	//}
	//if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
	//	_info.direction = E_RIGHT;
	//	_info.nextState = E_WALK;
	//}
	//if (KEYMANAGER->isStayKeyDown(VK_UP)) {
	//	_info.nextState = E_WALK;
	//	_info.pt.y -= 5;
	//}
	//if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
	//	_info.nextState = E_WALK;
	//	_info.pt.y += 5;
	//}
	//if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT)) {
	//	_info.nextState = E_IDLE;
	//}
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//{
	//	if (PtInRect(&_info.rc, _ptMouse))
	//	{
	//		_info.isHurt = true;
	//		_info.hp -= 5;
	//	}
	//}

	setState(_info.nextState);

}

void bandit::render(HDC hdc)
{
	_enState->render(hdc);
}

void bandit::setState(ENEMYSTATE state)
{
	if (_info.state == state) return;
	_info.state = state;
	switch (_info.state)
	{
	case E_IDLE:		_enState = new banditIdle;
		break;
	case E_WALK:		_enState = new banditWalk;
		break;
	case E_DEAD:		_enState = new banditDead;
		break;
	default:
		break;
	}
	_enState->init(_info);

}

