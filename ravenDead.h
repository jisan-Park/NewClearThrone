#pragma once
#include "ravenState.h"
class ravenDead :
	public ravenState
{
private:
	animation*	ravendeadright;
	animation*	ravendeadleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

