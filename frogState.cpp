#include "stdafx.h"
#include "frogState.h"

void frogState::setHurtAnimation()
{
	froghurtright = new animation;
	froghurtright->init("frog_hurt");
	froghurtright->setPlayFrame(0, 2, false, false, hurtFinish, this);
	froghurtright->setFPS(10);

	froghurtleft = new animation;
	froghurtleft->init("frog_hurt");
	froghurtleft->setPlayFrame(5, 3, false, false, hurtFinish, this);
	froghurtleft->setFPS(10);
}
