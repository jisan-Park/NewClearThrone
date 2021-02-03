#pragma once
#include "bigBanditState.h"
class bigBanditFire :
	public bigBanditState
{
private:
	animation* bigbanditfireright;
	animation* bigbanditfireleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

