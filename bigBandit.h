#pragma once
#include "enemy.h"
#include "bigBanditDead.h"
//#include "bigBanditDash.h"
#include "bigBanditFire.h"
#include "bigBanditIdle.h"
#include "bigBanditWalk.h"
class bigBandit :
	public enemy
{

private:
	weapon* _weapon;

public:
	virtual HRESULT init(float x, float y);

	virtual void update();

	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);

};

