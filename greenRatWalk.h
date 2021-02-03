#pragma once
#include "greenRatState.h"
class greenRatWalk : public greenRatState
{
private:
	animation* greenratwalkright;
	animation* greenratwalkleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

