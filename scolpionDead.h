#pragma once
#include "scolpionState.h"
class scolpionDead :
	public scolpionState
{
private:
	animation* scolpiondeadright;
	animation* scolpiondeadleft;

public:

	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);

};

