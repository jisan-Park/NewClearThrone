#pragma once
class camera
{
private:
	//Ä«¸Þ¶ó ÁÂÇ¥
	POINT _pt;
	
public:
	//setter
	void setPointX(int x) { _pt.x = x; };
	void setPointY(int y) { _pt.y = y; };
	void setPoint(int x, int y) { _pt.x = x; _pt.y = y; };
	//getter
	POINT getPoint() { return _pt; };
};

