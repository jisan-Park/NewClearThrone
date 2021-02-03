#pragma once
#include "enemy.h"
#include"greenFrogIdle.h"
#include"greenFrogWalk.h"
#include"greenFrogDead.h"

class greenFrog : public enemy
{
private:


public:
	virtual HRESULT init(float x, float y);

	virtual void update();

	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
};

