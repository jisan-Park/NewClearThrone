#pragma once
#include "bigRatState.h"
class bigRatAttack : public bigRatState
{
private:
	animation*	bigratattackright;
	animation*	bigratattackleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

