#pragma once
#include "enemy.h"
#include "maggotIdle.h"
#include "maggotDead.h"
class maggot : public enemy
{

private:

public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
};

