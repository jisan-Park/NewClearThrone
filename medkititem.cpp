#include "stdafx.h"
#include "medkititem.h"

HRESULT medkititem::init(float x, float y)
{
	_pt.x = x;
	_pt.y = y;
	_width = 5;
	_height = 5;
	currentFrameX = 0;
	_itemtype = MEDKETITEM;
	_img = new image;
	_img = IMAGEMANAGER->findImage("medkit_item");
	_rc = RectMakeCenter(_pt.x, _pt.y, _width, _height);
	return S_OK;
}
