#pragma once
#include "weapon.h"
class shovel : public weapon
{
public:
	virtual HRESULT init(POINT pt);
	virtual void update();
};

