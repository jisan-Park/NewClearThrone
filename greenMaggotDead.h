#pragma once
#include "greenMaggotState.h"
class greenMaggotDead :
	public greenMaggotState
{
private:
	animation* greenmaggothurtright;
	animation* greenmaggotdeadright;
	animation* greenmaggothurtleft;
	animation* greenmaggotdeadleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);

};

