#pragma once
#include "bigBanditState.h"
class bigBanditIdle :
	public bigBanditState
{
private:
	animation* bigbanditidleright;
	animation* bigbanditidleleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

