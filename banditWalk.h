#pragma once
#include "banditState.h"
class banditWalk :
	public banditState
{
private:
	animation* banditwalkright;
	animation* banditwalkleft;
public:
	virtual HRESULT init(enemyinfo info);

	virtual void update(enemyinfo &info);


};

