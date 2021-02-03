#pragma once
#include "ratState.h"
class ratWalk :
	public ratState
{
private:
	animation* ratwalkright;
	animation* ratwalkleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

