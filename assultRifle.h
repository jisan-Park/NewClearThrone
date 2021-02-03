#pragma once
#include "weapon.h"
class assultRifle :
	public weapon
{
public:
	virtual HRESULT init(POINT pt);
	virtual void update();
};

