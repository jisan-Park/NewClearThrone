#pragma once
#include "weapon.h"
class pistol :
	public weapon
{
public:
	virtual HRESULT init(POINT pt);
	virtual void update();
	virtual void fire();
};

