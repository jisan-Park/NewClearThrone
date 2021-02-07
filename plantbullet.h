#pragma once
#include "singletonBase.h"

class plantbullet : public singletonBase <plantbullet>
{
private:
	image* _img;				//총알의 이미지
	RECT _rc;
	POINT _pt;				//중점 좌표
	POINT _firept;			//발사할 때 좌표
	float _angle;			//각도
	float _radius;			//붼지름
	float _speed;			//스피드
	bool _isFire;			//발사했누?
	int _count;				//프레임 이미지 카운트용
	float _range;			//사거리
	int _bulletmax;
	animation* _motion;
	animation* _plantbullet;
	bool _ison;

public:
	plantbullet() {};
	~plantbullet() {};

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void fire(POINT pt, float speed, float angle);
	virtual void move();
	virtual void setAni();
	
	void collision();
	bool getIsfire() { return _isFire; }
	void setISfire(bool isfire) { _isFire = isfire; };
	RECT getRC() { return _rc; }
	image* getImage() { return _img; }
	void setImage(image* img) { _img = img; };
	void setMotion();
};


