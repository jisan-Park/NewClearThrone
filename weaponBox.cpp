#include "stdafx.h"
#include "weaponBox.h"

HRESULT weaponBox::init(float x, float y)
{
	_pt.x = x;
	_pt.y = y;
	_width = 30;
	_height = 30;
	currentFrameX = 0;
	_boxtype = WEAPONBOX;
	_img = new image;
	_img = IMAGEMANAGER->findImage("weapon_box");
	_rc = RectMakeCenter(_pt.x, _pt.y, _width, _height);
	_isOpen = false;
	return S_OK;
}
