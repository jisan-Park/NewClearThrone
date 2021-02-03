#include "stdafx.h"
#include "utils.h"

namespace TFIVE_UTIL
{
	float getDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return sqrtf(x * x + y * y);
	}

	float getDistance(POINT pt1, POINT pt2)
	{
		float x = pt2.x - pt1.x;
		float y = pt2.y - pt1.y;

		return sqrtf(x * x + y * y);
	}

	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		float angle = -atan2f(y, x);
		

		return angle;
	}

	float getAngle(POINT pt1, POINT pt2)
	{
		float x = pt2.x - pt1.x;
		float y = pt2.y - pt1.y;

		float angle = -atan2f(y, x);


		return angle;
	}


}