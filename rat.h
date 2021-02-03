#pragma once
#include "enemy.h"
#include "ratDead.h"
#include "ratIdle.h"
#include "ratWalk.h"

class rat : public enemy
{
private:


public:
	virtual HRESULT init(float x, float y);
	virtual void update();

	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);

};

