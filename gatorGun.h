#pragma once
#include "weapon.h"
class gatorGun : public weapon
{
	virtual HRESULT init(POINT pt, weaponState state);
	virtual void update();
	virtual void fire();
};

