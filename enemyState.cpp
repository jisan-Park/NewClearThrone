#include "stdafx.h"
#include "enemyState.h"

enemyState::enemyState()
{
}

enemyState::~enemyState()
{
}


HRESULT enemyState::init(enemyinfo info)
{
	return S_OK;
}

void enemyState::update(enemyinfo &info)
{
}

void enemyState::release()
{
}

void enemyState::render(HDC hdc)
{
	_img->aniRender(hdc, _pt.x, _pt.y, _motion);
}

void enemyState::init(image * img, animation * ani, int x, int y)
{
}


void enemyState::setRect()
{
}

void enemyState::hurtFinish(void * obj)
{
	enemyState*e = (enemyState*)obj;
	e->setHurt(false);
}
