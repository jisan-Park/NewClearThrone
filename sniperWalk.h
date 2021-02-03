#pragma once
#include "sniperState.h"
class sniperWalk :
	public sniperState
{
	animation* sniperwalkright;
	animation* sniperwalkleft;
	animation* sniperhurtright;
	animation* sniperhurtleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

