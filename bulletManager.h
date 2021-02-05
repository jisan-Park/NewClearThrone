#pragma once
#include "singletonBase.h"
#include "bullet16.h"
#include "bullet1.h"
#include <vector>
enum BULLETTYPE
{
	ANGLE16,
	ANGLE1,
	FLAME,
};
class bulletManager : public singletonBase<bulletManager>
{
private:
	typedef vector<bullet*> vBullet;
	typedef vector<bullet*>::iterator viBullet;

private:
	vBullet _vBullet;
	viBullet _viBullet;

public:
	bulletManager() {};
	~bulletManager() {};
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void fire(BULLETTYPE type, POINT pt, float speed, float angle, int damage, whoshot who);
	void removeBullet(int i);

	vBullet getvBullet() { return _vBullet; };
	viBullet getViBullet() { return _viBullet; };


};

