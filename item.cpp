#include "stdafx.h"
#include "item.h"

HRESULT item::init(float x, float y)
{
	return S_OK;
}

void item::release()
{
}

void item::update()
{
}

void item::render(HDC hdc)
{
	_img->frameRender(hdc, _pt.x - 15, _pt.y - 15, currentFrameX, 0);
}
