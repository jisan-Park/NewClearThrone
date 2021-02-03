#pragma once
#include "ratState.h"

class ratDead :	public ratState
{

private:
	animation* ratdeadright;
	animation* ratdeadleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

