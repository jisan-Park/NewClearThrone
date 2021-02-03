#pragma once
#include "enemy.h"
#include "bigMaggotBurrow.h"
#include "bigMaggotDead.h"
#include "bigMaggotIdle.h"

class bigMaggot : public enemy
{
private:



public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
};

