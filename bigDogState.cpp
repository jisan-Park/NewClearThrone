#include "stdafx.h"
#include "bigDogState.h"

void bigDogState::hurtFinish(void * obj)
{
	bigDogState*b = (bigDogState*)obj;
	b->setHurt(false);
}
