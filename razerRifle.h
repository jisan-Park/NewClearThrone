#pragma once
#include "weapon.h"
class razerRifle :
	public weapon
{
public:
	virtual HRESULT init(POINT pt);
	virtual void update();
};

