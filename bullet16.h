#pragma once
#include "bullet.h"
class bullet16 :
	public bullet
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;
	int _index;	// 16방 이미지 프레임인덱스입니다
	float _range;
	float _turnangle;
public:
	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void fire(POINT pt, float speed, float angle, whoshot who);
	virtual void fire(POINT pt, float speed, float angle, float turnangle, whoshot who);
	virtual void setFrameIndex();

	virtual void move();
};

