#pragma once
#include "bullet.h"
class shotGunBullet :
	public bullet
{
virtual	HRESULT init();
virtual void release();
virtual void update();
virtual void render(HDC hdc);

virtual void fire(POINT pt, float speed, float angle, int damage);
virtual void setFrameIndex();

virtual void move();
};

