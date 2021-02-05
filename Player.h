#pragma once
#include "singletonBase.h"
#include "assultRifle.h"
#include "grenadeLauncher.h"
#include "machineGun.h"
#include "pistol.h"
#include "razerRifle.h"
#include "shotGun.h"
#include "shovel.h"
#include "sword.h"
#include "triplemachinegun.h"

enum MOVEDIRCTION
{
	NOMOVE,
	RIGHTMOVE,
	LEFTMOVE,
	UPMOVE,
	DOWNMOVE
};

enum DIRECTION
{
	RIGHT,
	LEFT
};

enum PLAYERSTATE
{
	IDLE,
	WALK,
	HURT,
	DEAD,
	SKILL
};

class Player
{
protected:
	POINT _pt;				//xy 좌표입니다
	float _width, _height;	//너비 높이입니다
	RECT _rc;				//충돌판정용 렉트입니다
	int _speed;				//움직이는 속도입니다
	int _damage;			//데미지입니다
	int _firecnt;			//발사 쿨입니다
	float _aimAngle;		//조준각입니다
	float _moveAngle;		//이동각입니다
	image* _img;			//이미지 입니다
	animation* _motion;		//애니메이션 모션
	bool _ishit;			//픽격확인
	int _maxhp;				//총HP
	int _hp;				//HP
	bool _isdead;			//죽는 조건
	int _playerbullet;		//현제 총알 갯수
	int _playerbulletMax;	//최대 총알 갯수

	//=========================================
	bool _isdash;//fish 스킬 트리거
	float _pushp;//fish 스킬 미는 힘
	//=========================================
	PLAYERSTATE _playerstate;
	DIRECTION _direction;
	MOVEDIRCTION _movedirctionx;
	MOVEDIRCTION _movedirctiony;

	weapon* _currentWeapon;
	weapon* _readyWeapon;
public:
	Player();
	~Player();

	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void release();

	virtual void render(HDC hdc);

	virtual void attack();
	virtual void move();
	virtual void setAnimation();
	//콜백을 위한 겟터,셋터
	//=========================================
	DIRECTION getDirection() { return _direction; }
	void setDirection(DIRECTION direction) { _direction = direction; }

	PLAYERSTATE getState() { return _playerstate; }
	void setState(PLAYERSTATE state) { _playerstate = state; }

	image* getImage() { return _img; }
	void setImage(image* img) { _img = img; }

	animation* getMotion() { return _motion; }
	void setteMotion(animation* ani) { _motion = ani; }

	void setIshit(bool ishit) { _ishit = ishit; }

	void setIsdead(bool isdead) { _isdead = isdead; }
	//=========================================
	POINT getPt() { return _pt; }
	void setPT(POINT pt) { _pt = pt; }

	RECT getRect() { return _rc; };

	int getPlayerbullet() { return _playerbullet; }
	void setPlayerbullet(int playerbullet) { _playerbullet = playerbullet; }

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }

	int getMaxhp() { return _maxhp; }
	void setMaxhp(int maxhp) { _maxhp = maxhp; }


	weapon* getWeapon() { return _currentWeapon; }

};
