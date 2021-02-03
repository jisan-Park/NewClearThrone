#pragma once
#include "weapon.h"
class wrench : public weapon
{
public:
	virtual HRESULT init(POINT pt);
	virtual void update();
};

