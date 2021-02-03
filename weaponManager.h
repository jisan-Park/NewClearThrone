#pragma once
#include "singletonBase.h"
#include "assultRifle.h"
#include "grenadeLauncher.h"
#include "machineGun.h"
#include "pistol.h"
#include "razerRifle.h"
#include "shotGun.h"
class weaponManager: public singletonBase <weaponManager>
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

