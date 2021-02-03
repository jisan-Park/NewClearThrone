#pragma once
#include "enemy.h"
#include "maggotNestIdle.h"
#include "maggotNestDead.h"
class maggotNest :
	public enemy
{

private:

public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
};

