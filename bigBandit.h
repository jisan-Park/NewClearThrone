#pragma once
#include "enemy.h"
#include "bigBanditDead.h"
#include "bigBanditFire.h"
#include "bigBanditIdle.h"
#include "bigBanditWalk.h"
class bigBandit :
	public enemy
{

private:
	animation* bigbanditidleright;
	animation* bigbanditwalkright;
	animation* bigbanditdashright;
	animation* bigbandithurtright;
	animation* bigbanditfireright;
	animation* bigbanditdeadright;

	animation* bigbanditidleleft;
	animation* bigbanditwalkleft;
	animation* bigbanditdashleft;
	animation* bigbandithurtleft;
	animation* bigbanditfireleft;
	animation* bigbanditdeadleft;

public:
	virtual HRESULT init(float x, float y);

	virtual void update();

	virtual void render(HDC hdc);

	virtual void setState(ENEMYSTATE state);

};

