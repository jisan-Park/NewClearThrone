#pragma once
#include "ravenState.h"
class ravenIdle :
	public ravenState
{
private:
	animation*	ravenhurtright;
	animation*	ravenidleright;
	animation*	ravenhurtleft;
	animation*	ravenidleleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

