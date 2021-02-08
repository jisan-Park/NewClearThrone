#pragma once
#include "enemy.h"
#include "assassinDead.h"
#include "assassinIdle.h"
#include "assassinWalk.h"

class assassin :
	public enemy
{
private:

public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
	void meleeattack();
};

