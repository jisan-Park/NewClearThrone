#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init(float x, float y)
{
	return S_OK;
}

void enemy::update()
{
}

void enemy::release()
{
}

void enemy::render(HDC hdc)
{
	//_img->aniRender(hdc, _x, _y, _motion);
}

void enemy::attack()
{
}

void enemy::move()
{
}

void enemy::setAnimation()
{
}

void enemy::setState(ENEMYSTATE state)
{
	
}
