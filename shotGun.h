#pragma once
#include "weapon.h"
class shotGun :
	public weapon
{
public:
	virtual HRESULT init(POINT pt, weaponState state);
	virtual void update();
};

