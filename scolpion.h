#pragma once
#include "enemy.h"
#include "scolpionIdle.h"
#include "scolpionFire.h"
#include "scolpionWalk.h"
#include "scolpionDead.h"

class scolpion :
	public enemy
{
private:

public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);

};

