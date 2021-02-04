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

	virtual void setState(ENEMYSTATE state);
	virtual ENEMYTYPE getEnemyType() { return _enemyType; };
	virtual enemyinfo getInfo() { return _info; };
	bool inRange();
	float EtoPAngle();

};

