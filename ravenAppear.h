#pragma once
#include "ravenState.h"
class ravenAppear :
	public ravenState
{
private:
	animation*	ravenlandright;
	animation*	ravenlandleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);

	static void appearidle(void *obj);
};

