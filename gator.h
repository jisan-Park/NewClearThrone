#pragma once
#include "enemy.h"
#include "gatorIdle.h"
#include "gatorWalk.h"
#include "gatorDead.h"

class gator : public enemy
{
private:

public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
};

