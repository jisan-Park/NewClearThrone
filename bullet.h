#pragma once
#include <vector>
enum BULLETTYPE
{
	ANGLE16,
	ANGLE1,
	FLAME,
	GRENADE,
	SHOTGUNBULLET,
	LASERBULLET,

	E_ANGLE16_1,
	E_ANGLE16_2,
	E_SHOTGUN,
	E_SHOTGUN2

};
class bullet
{
protected:

	//tagBullet _bullet;
	image* _img;				//총알의 이미지
	RECT _rc;
	POINT _pt;				//중점 좌표
	POINT _firept;			//발사할 때 좌표

	BULLETTYPE _type;
	float _angle;			//각도
	float _radius;			//붼지름
	float _speed;			//스피드
	bool _isFire;			//발사했누?
	int _count;				//프레임 이미지 카운트용
	int _damage;
	float _range;			//사거리

	bool _gone;
public:
	bullet() {};
	~bullet() {};

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void fire(POINT pt, float speed, float angle, int damage);
	void setFrameIndex8();
	virtual void move();
	virtual void explode();

	RECT getRect() { return _rc; }
	float getAngle() { return _angle; }
	int getDamage() { return _damage; }
	bool getGone() { return _gone; }
	POINT getPt() { return _pt; }
	float getSpeed() { return _speed; }
	BULLETTYPE getType() { return _type; }
};

