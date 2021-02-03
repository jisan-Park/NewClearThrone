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
	animation* salamanderfireright;
	animation* salamanderdeadright;
	animation* salamanderhurtright;
	animation* salamanderidleright;
	animation* salamanderwalkright;

	animation* salamanderfireleft;
	animation* salamanderdeadleft;
	animation* salamanderhurtleft;
	animation* salamanderidleleft;
	animation* salamanderwalkleft;
public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
	virtual void setAnimation();
};

