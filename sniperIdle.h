#pragma once
#include "sniperState.h"
class sniperIdle :
	public sniperState
{
private:
	animation* sniperidleright;
	animation* sniperidleleft;
	animation* sniperhurtright;
	animation* sniperhurtleft;


public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

