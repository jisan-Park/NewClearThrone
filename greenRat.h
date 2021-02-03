#pragma once
#include "enemy.h"
#include "greenRatDead.h"
#include "greenRatIdle.h"
#include "greenRatWalk.h"
class greenRat : public enemy
{
private:


public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);

};

