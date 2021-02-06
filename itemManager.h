#pragma once
#include "singletonBase.h"
#include <vector>
#include "itemBox.h"
#include"bulletBox.h"
#include"weaponBox.h"
#include"medkitBox.h"
#include "item.h"
#include "bulletitem.h"
#include "medkititem.h"
enum ITEMBOXTYPE
{
	BULLETITEMBOX,
	WEAPOMITEMBOX,
	MEDKITITEMBOX
};

class itemManager : public singletonBase<itemManager>
{
private:
	typedef vector<itemBox*> vItembox;
	typedef vector<itemBox*>::iterator viItembox;

	typedef vector<weapon*> vWeapon;
	typedef vector<weapon*>::iterator viWeapon;

	typedef vector<item*> vItem;
	typedef vector<item*>::iterator viItem;

	vItembox _vItembox;
	viItembox _viItembox;

	vWeapon _vWeapon;
	viWeapon _viWeapon;

	vItem _vItem;
	viItem _viItem;

	weaponType _weaponType;

	ITEMBOXTYPE _itemboxtype;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void weaponSwap();
	virtual void setimage();
	virtual void setItembox(ITEMBOXTYPE itemboxtype, POINT PT);
	virtual void collsion();
	void createWeapon(POINT pt);

};

