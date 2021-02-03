#pragma once
#include "weapon.h"
class machineGun :
	public weapon
{
public:
	virtual HRESULT init(POINT pt);
	virtual void update();
};

