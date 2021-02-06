#pragma once
#include "enemy.h"
#include "ravenDead.h"
#include "ravenIdle.h"
#include "ravenWalk.h"
#include "ravenAppear.h"
#include "ravenBurrow.h"

class raven :
	public enemy
{
private:


public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
	//virtual void setAnimation();
};

