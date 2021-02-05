#pragma once
#include "weapon.h"
class shovel : public weapon
{
public:
	virtual HRESULT init(POINT pt, weaponState state);
	virtual void render(HDC hdc);
	virtual void update();
	virtual void fire();
};

