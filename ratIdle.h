#pragma once
#include "ratState.h"
class ratIdle :
	public ratState
{
private:
	animation* ratidleright;
	animation* ratidleleft;
public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

