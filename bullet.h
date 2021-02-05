#pragma once
#include <vector>
enum whoshot
{
	PLAYER,
	ENEMY
};
//struct tagBullet
//{
//	image* img;				//총알의 이미지
//	RECT rc;
//	POINT pt;				//중점 좌표
//	POINT firept;			//발사할 때 좌표
//	whoshot who;
//	float angle;			//각도
//	float radius;			//붼지름
//	float speed;			//스피드
//	bool isFire;			//발사했누?
//	int count;				//프레임 이미지 카운트용
//	int damage;
//};
class bullet
{
protected:

	//tagBullet _bullet;
	image* _img;				//총알의 이미지
	RECT _rc;
	POINT _pt;				//중점 좌표
	POINT _firept;			//발사할 때 좌표
	whoshot _who;
	float _angle;			//각도
	float _radius;			//붼지름
	float _speed;			//스피드
	bool _isFire;			//발사했누?
	int _count;				//프레임 이미지 카운트용
	int _damage;
	float _range;			//사거리
public:
	bullet() {};
	~bullet() {};

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void fire(POINT pt, float speed, float angle, int damage, whoshot who);
	virtual void move();

	RECT getRect() { return _rc; }
	float getAngle() { return _angle; }
	whoshot getWho() { return _who; }

};

