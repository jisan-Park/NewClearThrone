#include "stdafx.h"
#include "banditState.h"

void banditState::hurtFinish(void * obj)
{
	banditState*b = (banditState*)obj;
	b->setHurt(false);
}
