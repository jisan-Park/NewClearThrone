#pragma once
#include "banditGun.h"
class sniperGun : public banditGun
{
public:

	HRESULT init(POINT pt, weaponState state);
	virtual void update();
	virtual void fire();
};

