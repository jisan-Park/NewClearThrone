#pragma once

enum ITEMTYPE
{
	BULLETITEM,
	MEDKETITEM
};
class item
{
protected:
	POINT _pt;
	float _width, _height;
	int currentFrameX, currentFrameY;
	RECT _rc;
	image* _img;
	ITEMTYPE _itemtype;
	
public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	RECT getItemRc() { return _rc; };
	void setItemRc(RECT rc) { _rc = rc; };

	POINT getItemPt() { return _pt; };
	void setItemPt(POINT pt) { _pt = pt; };

	ITEMTYPE getItemtype() { return _itemtype; };
	void setItemtype(ITEMTYPE itemtype) { _itemtype = itemtype; };
};

