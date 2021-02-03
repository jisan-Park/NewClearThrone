#pragma once
#include "ravenState.h"
class ravenFly :
	public ravenState
{
private:
	animation*	ravenflyright;
	animation*	ravenflyleft;

	animation*	ravenlandright;
	animation*	ravenliftright;
	animation*	ravenlandleft;
	animation*	ravenliftleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

