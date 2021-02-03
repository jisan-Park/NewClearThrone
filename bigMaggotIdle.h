#pragma once
#include "bigMaggotState.h"
class bigMaggotIdle :
	public bigMaggotState
{
private:
	animation* bigmaggotidleright;
	animation* bigmaggotidleleft;

	animation* bigmaggothurtright;
	animation* bigmaggothurtleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

