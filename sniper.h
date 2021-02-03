#pragma once
#include "enemy.h"
#include "sniperDead.h"
#include "sniperIdle.h"
#include "sniperWalk.h"

class sniper :
	public enemy
{
private:
public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
};

