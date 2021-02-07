#pragma once
#include "singletonBase.h"
#include "assultRifle.h"
#include "grenadeLauncher.h"
#include "machineGun.h"
#include "pistol.h"
#include "razerRifle.h"
#include "shotGun.h"
#include "banditGun.h"
#include "bigBanditGun.h"
#include "gatorGun.h"
#include "wrench.h"
class weaponManager : public singletonBase <weaponManager>
{
private:
	razerRifle* test;
public:
	weaponManager() {};
	~weaponManager() {};
	void init();
	void release();
	void update();
	void render(HDC hdc);

	void setImage();
};

