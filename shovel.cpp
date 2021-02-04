#include "stdafx.h"
#include "shovel.h"

HRESULT shovel::init(POINT pt)
{
	_img = IMAGEMANAGER->findImage("shovel");
	_pt = pt;
	_radius = 20;
	_state = NOWUSING;
	_type = SHOVEL;
	_radius = 20;
	_damage = 20;
	_coolDown = 15;
	_angle = 0;
	return S_OK;
}

void shovel::render(HDC hdc)
{
	_img->frameRender(hdc, _imgx - _img->getFrameWidth() / 2, _imgy - _img->getFrameHeight() / 2, _index, 0);
}

void shovel::update()
{

	setFrameIndex(_angle);
	Position();
	_pt = PLAYERMANAGER->getPlayer()->getPt();
}

void shovel::fire()
{
	_meleeAngle *= (-1);
}
