#pragma once
#include "singletonBase.h"
#include "bullet16.h"
#include "bullet1.h"
#include "grenade.h"
#include "enemyBullet16_1.h"
#include "enemyBullet16_2.h"
#include "enemyShotGun.h"
#include "enemyShotGun2.h"
#include "shotGunBullet.h"
#include "laserBullet.h"
#include <vector>
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

	//변이 카드 변수
	bool _isEuphoria;
	bool _isScareFace;
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

	//변이 카드 함수
	void Euphoria();
	void ScareFace();

	vBullet getvEnemyBullet() { return _vEnemyBullet; };
	viBullet getViEnemyBullet() { return _viEnemyBullet; };

	vBullet getvPlayerBullet() { return _vPlayerBullet; };
	viBullet getViPlayerBullet() { return _viPlayerBullet; };


};

