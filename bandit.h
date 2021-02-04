#pragma once
#include "enemy.h"
#include"banditIdle.h"
#include"banditWalk.h"
#include"banditDead.h"

class bandit : public enemy
{
	weapon* _weapon;
public:
	virtual HRESULT init(float x, float y);

	virtual void update();

	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);

};