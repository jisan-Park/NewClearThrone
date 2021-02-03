#pragma once
#include "maggotState.h"
class maggotIdle :
	public maggotState
{
private:
	animation* maggotidleright;
	animation* maggotidleleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);

};

