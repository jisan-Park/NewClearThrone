#pragma once
#include "maggotNestState.h"
class maggotNestIdle :
	public maggotNestState
{
private:
	animation* maggotnestidleright;
	animation* maggotnestidleleft;
	animation* maggotnesthurtright;
	animation* maggotnesthurtleft;
public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

