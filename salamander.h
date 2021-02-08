#pragma once
#include "enemy.h"
#include "salamanderDead.h"
#include "salamanderIdle.h"
#include "salamanderWalk.h"
#include "salamanderFire.h"
class salamander :
	public enemy
{
private:

public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
	
};

