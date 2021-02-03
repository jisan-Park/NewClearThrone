#pragma once
#include "salamanderState.h"
class salamanderIdle :
	public salamanderState
{
private:
	animation* salamanderhurtright;
	animation* salamanderidleright;
	animation* salamanderhurtleft;
	animation* salamanderidleleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

