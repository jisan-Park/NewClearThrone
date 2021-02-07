#pragma once
#include "frogState.h"
#include "frog.h"
class frogDead : public frogState
{
private:
	animation* frogdeadright;
	animation* frogdeadleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);

	void deadEffect();
};

