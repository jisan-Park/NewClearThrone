#pragma once
#include "enemy.h"
#include "greenMaggotDead.h"
#include "greenMaggotIdle.h"

class greenMaggot : public enemy
{
private:

public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
};

