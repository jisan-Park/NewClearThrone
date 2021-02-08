#pragma once
#include "enemyState.h"
class bigDogState : public enemyState
{
protected:
	animation* bigdogidlehurtright;
	animation* bigdogidlehurtleft;

	animation* bigdogspinhurt;

	static void hurtFinish(void * obj);

};

