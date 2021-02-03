#pragma once
#include "bigMaggotState.h"
class bigMaggotDead :
	public bigMaggotState
{
private:
	animation* bigmaggotdeadright;
	animation* bigmaggotdeadleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);

};

