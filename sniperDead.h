#pragma once
#include "sniperState.h"
class sniperDead :
	public sniperState
{
private:
	animation* sniperdeadright;
	animation* sniperdeadleft;
public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

