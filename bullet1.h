#pragma once
#include "bullet.h"
class bullet1 :
	public bullet
{
public:
	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void fire(POINT pt, float speed, float angle, int damage, whoshot who);
	virtual void setFrameIndex();

	virtual void move();
};

