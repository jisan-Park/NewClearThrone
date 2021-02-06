#pragma once 
#include "enemyState.h"
enum ENEMYTYPE;
class enemy
{
protected:
	enemyinfo _info;
	enemyState* _enState;
	ENEMYTYPE _enemyType;
	int _rndMoveCnt = 0;
	int _rndInterval;
	int _fireCnt = 0;
public:
	enemy();
	~enemy();

	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void release();

	virtual void render(HDC hdc);

	virtual void attack();
	virtual void move();
	virtual void setAnimation();
	void collision();
	void explosion(POINT pt, float range, int damage);
	void meleecollision(POINT pt, float range, int damage);
	void eyeSkill(int x, int y);

	virtual void setState(ENEMYSTATE state);
	virtual ENEMYTYPE getEnemyType() { return _enemyType; };
	virtual enemyinfo getInfo() { return _info; };
	void decreaseHP(int i) { _info.hp -= i; };
	bool inRange();
	float EtoPAngle();
	float EtoPAngleRnd();
};

