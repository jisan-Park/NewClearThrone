#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>
#include "enemy.h"
#include "bandit.h"
#include "bigBandit.h"
#include "bigMaggot.h"
#include "greenMaggot.h"
#include "maggot.h"
#include "maggotNest.h"
#include "scolpion.h"
#include "bigRat.h"
#include "frog.h"
#include "gator.h"
#include "greenFrog.h"
#include "greenRat.h"
#include "rat.h"
#include "assassin.h"
#include "bigDog.h"
#include "raven.h"
#include "salamander.h"
#include "sniper.h"

enum ENEMYTYPE
{
	//STAGE1 0-6
	BIGBANDIT,
	BANDIT,
	BIGMAGGOT,
	MAGGOT,
	GREENMAGGOT,
	SCOLPION,
	MAGGOTNEST,

	//STAGE2 7-12
	BIGRAT,
	RAT,
	GREENRAT,
	FROG,
	GREENFROG,
	GATOR,

	//STAGE3 13-17
	BIGDOG,
	ASSASSIN,
	RAVEN,
	SALAMADER,
	SNIPER
};

class enemyManager : public singletonBase<enemyManager>
{
private:
	//에너미 벡터
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

	typedef map<string, vEnemy> mvEnemy;
	typedef map<string, vEnemy>::iterator mviEnemy;

private:
	//이름별 에너미 벡터 저장용
	mvEnemy _mvEnemy;
	//보여주기용 에너미 벡터
	vEnemy _showEnemy;
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setimage();
	void addEnemys(string strKey, ENEMYTYPE enemyType, int x, int y);
	void deleteEnemys(string strKey, int x, int y);
	vector<enemy*> getEnemys(string strKey);

	//create
	void createMaggot(POINT pt);
	void createGreenMaggot(POINT pt);
	//setter
	void setShowEnemyVector(string strKey);
	void clearShowEnemyVector() { _showEnemy.clear(); };
	void createRandomEnemyVector();
	void removeEnemy(int i);
	void plantSkill();
	//getter
	vEnemy getShowEnemyVector() { return _showEnemy; };
};

