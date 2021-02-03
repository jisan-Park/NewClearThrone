#pragma once
#include "singletonBase.h"
#include <vector>
enum whoshot
{
	PLAYER,
	ENEMY
};
struct tagBullet
{
	image* img;				//총알의 이미지
	RECT rc;
	POINT pt;				//중점 좌표
	POINT firept;			//발사할 때 좌표
	whoshot who;
	float angle;			//각도
	float radius;			//붼지름
	float speed;			//스피드
	bool isFire;			//발사했누?
	int count;				//프레임 이미지 카운트용
};
class bullet : singletonBase<bullet>
{
protected:
	vector <tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;			//사거리
public:
	bullet() {};
	~bullet() {};

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	void removeBullet(int arrnum);

	virtual void fire(POINT pt, float speed, float angle, whoshot who);
	virtual void fire(POINT pt, float speed, float angle, float turnangle, whoshot who);
	virtual void move();

	vector<tagBullet> getVbullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

};

