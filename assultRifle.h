#pragma once
#include "weapon.h"
class assultRifle :
	public weapon
{
private:
	int _bulletInterval;
	int _cnt;
	bool _fired;
public:
	virtual HRESULT init(POINT pt, weaponState state);
	virtual void update();
	virtual void fire();
	virtual void followingFire();
};

