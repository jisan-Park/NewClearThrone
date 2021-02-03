#pragma once
#include "greenMaggotState.h"
class greenMaggotIdle :
	public greenMaggotState
{
private:
	animation* greenmaggotidleright;
	animation* greenmaggotidleleft;


public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);

};

