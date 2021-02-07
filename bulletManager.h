#pragma once
#include "singletonBase.h"
#include "bullet16.h"
#include "bullet1.h"
#include "grenade.h"
#include "enemyBullet16_1.h"
#include "enemyBullet16_2.h"
#include <vector>
enum BULLETTYPE
{
	ANGLE16,
	ANGLE1,
	FLAME,
	GRENADE,

	E_ANGLE16_1,
	E_ANGLE16_2
};
class bulletManager : public singletonBase<bulletManager>
{
private:
	typedef vector<bullet*> vBullet;
	typedef vector<bullet*>::iterator viBullet;

private:
	vBullet _vEnemyBullet;
	viBullet _viEnemyBullet;

	vBullet _vPlayerBullet;
	viBullet _viPlayerBullet;

public:
	bulletManager() {};
	~bulletManager() {};
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void PlayerFire(BULLETTYPE type, POINT pt, float speed, float angle, int damage);
	void EnemyFire(BULLETTYPE type, POINT pt, float speed, float angle, int damage);
	void removePlayerBullet(int i);
	void removeEnemyBullet(int i);

	void wallCollision();

	vBullet getvEnemyBullet() { return _vEnemyBullet; };
	viBullet getViEnemyBullet() { return _viEnemyBullet; };

	vBullet getvPlayerBullet() { return _vPlayerBullet; };
	viBullet getViPlayerBullet() { return _viPlayerBullet; };


};

