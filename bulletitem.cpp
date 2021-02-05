#include "stdafx.h"
#include "bulletitem.h"

HRESULT bulletitem::init(float x, float y)
{
	_pt.x = x;
	_pt.y = y;
	_width = 5;
	_height = 5;
	currentFrameX = 0;
	_itemtype = BULLETITEM;
	_img = new image;
	_img = IMAGEMANAGER->findImage("bullet_item");
	_rc = RectMakeCenter(_pt.x, _pt.y, _width, _height);
	return S_OK;
}
