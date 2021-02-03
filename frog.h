#pragma once
#include "enemy.h"
#include "frogIdle.h"
#include "frogWalk.h"
#include "frogDead.h"
class frog :
	public enemy
{
private:

public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
	
};

