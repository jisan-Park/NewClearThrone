#include "stdafx.h"
#include "itemBox.h"

HRESULT itemBox::init(float x, float y)
{
	return S_OK;
}

void itemBox::release()
{
}

void itemBox::update()
{
	if (_isOpen)
	{
		currentFrameX = 7;
		if (_img->getMaxFrameX() < 7)
		{
			currentFrameX = 5;
		}
	}
	else
	{
		currentFrameX = 0;
	}
}

void itemBox::render(HDC hdc)
{
	_img->frameRender(hdc, _pt.x - 15, _pt.y - 15, currentFrameX, 0);
}
