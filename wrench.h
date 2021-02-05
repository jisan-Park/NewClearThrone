#pragma once
#include "weapon.h"
class wrench : public weapon
{
public:
	virtual HRESULT init(POINT pt, weaponState state);
	virtual void update();
};

