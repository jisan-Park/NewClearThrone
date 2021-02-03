#pragma once
#include "banditState.h"
class banditIdle :
	public banditState
{
private:
	animation* banditidleright;
	animation* banditidleleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);

};

