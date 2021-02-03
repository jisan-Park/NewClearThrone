#pragma once
#include "weapon.h"
class shotGun :
	public weapon
{
public:
	virtual HRESULT init(POINT pt);
	virtual void update();
};

