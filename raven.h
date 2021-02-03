#pragma once
#include "enemy.h"
#include "ravenDead.h"
#include "ravenFly.h"
#include "ravenIdle.h"
#include "ravenWalk.h"

class raven :
	public enemy
{
private:
	//animation*	ravendeadright;
	//animation*	ravenflyright;
	//animation*	ravenhurtright;
	//animation*	ravenidleright;
	//animation*	ravenlandright;
	//animation*	ravenliftright;
	//animation*	ravenwalkright;
	//
	//animation*	ravendeadleft;
	//animation*	ravenflyleft;
	//animation*	ravenhurtleft;
	//animation*	ravenidleleft;
	//animation*	ravenlandleft;
	//animation*	ravenliftleft;
	//animation*	ravenwalkleft;

public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);
	//virtual void setAnimation();
};

