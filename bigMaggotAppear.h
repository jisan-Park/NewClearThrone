#pragma once
#include "bigMaggotState.h"
class bigMaggotAppear : public bigMaggotState
{

private:
	animation* bigmaggotappearright;
	animation* bigmaggotappearleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);

	static void appearidle(void *obj);
};

