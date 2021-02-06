#pragma once
#include "weapon.h"
class bigBanditGun :
	public weapon
{
public:
	virtual HRESULT init(POINT pt, weaponState state);
	virtual void update();
	virtual void fire();
};

