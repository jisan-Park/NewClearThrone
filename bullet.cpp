#include "stdafx.h"
#include "bullet.h"

HRESULT bullet::init()
{
	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	move();
}

void bullet::render(HDC hdc)
{
}


void bullet::fire(POINT pt, float speed, float angle, int damage, whoshot who)
{
}


void bullet::move()
{
	
}


