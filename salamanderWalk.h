#pragma once
#include "salamanderState.h"
class salamanderWalk :
	public salamanderState
{
private:
	animation* salamanderhurtright;
	animation* salamanderhurtleft;
	animation* salamanderwalkright;
	animation* salamanderwalkleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

