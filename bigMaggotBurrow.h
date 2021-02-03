#pragma once
#include "bigMaggotState.h"
class bigMaggotBurrow :
	public bigMaggotState
{
private:
	animation* bigmaggotburrowright;
	animation* bigmaggotburrowleft;
	animation* bigmaggotappearright;
	animation* bigmaggotappearleft;
public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);

};

