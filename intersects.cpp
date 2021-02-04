#include "stdafx.h"
#include "intersects.h"

bool intersects(RECT rc, POINT start, POINT end)
{
	float width = rc.right - rc.left;
	float height = rc.bottom - rc.top;
	float minX = start.x;
	float maxX = end.x;

	if (start.x > end.x) {
		minX = end.x;
		maxX = start.x;
	}

	if (maxX > rc.left + width)
		maxX = rc.left + width;

	if (minX < rc.left)
		minX = rc.left;

	if (minX > maxX)
		return false;

	float minY = start.y;
	float maxY = end.y;

	float dx = end.x - start.x;

	if (abs(dx) > 0.0000001)
	{
		float a = (end.y - start.y) / dx;
		float b = start.y - a * start.x;
		minY = a * minX + b;
		maxY = a * maxX + b;
	}

	if (minY > maxY) {
		float tmp = maxY;
		maxY = minY;
		minY = tmp;
	}

	if (maxY > rc.top + height)
		maxY = rc.top + height;

	if (minY < rc.top)
		minY = rc.top;

	if (minY > maxY)
		return false;

	return true;
}
