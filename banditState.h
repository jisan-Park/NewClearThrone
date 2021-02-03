#pragma once
#include "enemyState.h"
class banditState :
	public enemyState
{
protected:
	animation* bandithurtright;
	animation* bandithurtleft;


	static void hurtFinish(void* obj);
};

