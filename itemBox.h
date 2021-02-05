#pragma once

enum BOXTYPE
{
	BULLETBOX,
	MEDKITBOX,
	WEAPONBOX
};

class itemBox
{
protected:
	POINT _pt;
	float _width, _height;
	int currentFrameX, currentFrameY;
	RECT _rc;
	image* _img;
	image* _bulletimg;
	bool _isOpen;
	BOXTYPE _boxtype;

public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);




	//=====================================
	bool getIsopen() { return _isOpen; };
	void setIsopen(bool isOpen) { _isOpen = isOpen; };

	RECT getItemboxRc() { return _rc; };
	void setItemboxRc(RECT rc) { _rc = rc; };

	POINT getItemPt() { return _pt; };
	void setItemPt(POINT pt) { _pt = pt; };

	BOXTYPE getBoxtype() { return _boxtype; };
	void setBoxtype(BOXTYPE boxtype) { _boxtype = boxtype; };
	//=====================================
};

