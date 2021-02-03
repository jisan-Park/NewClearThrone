#pragma once
#include "weapon.h"
class sword : public weapon
{
public:
	virtual HRESULT init(POINT pt);
	virtual void update();
};

