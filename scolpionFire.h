#pragma once
#include "scolpionState.h"
class scolpionFire :
	public scolpionState
{
private:
	animation* scolpionfireright;
	animation* scolpionfireleft;

public:

	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

