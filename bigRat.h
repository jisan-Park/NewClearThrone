#pragma once
#include "enemy.h"
#include "bigRatIdle.h"
#include "bigRatAttack.h"
#include "bigRatDead.h"
#include "bigRatFire.h"
#include "bigRatWalk.h"

class bigRat :
	public enemy
{
private:

public:
	virtual HRESULT init(float x, float y);

	virtual void update();

	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
};

