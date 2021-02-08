#include "stdafx.h"
#include "enemyManager.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	setimage();
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{

}

void enemyManager::render(HDC hdc)
{
}

void enemyManager::setimage()
{
	//stage1
	IMAGEMANAGER->addFrameImage("bandit_bullet", "image/enemy/stage1/bandit_bullet.bmp", 512, 32, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bandit_bullet_effect", "image/enemy/stage1/bandit_bullet_effect.bmp", 320, 64, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bandit_dead", "image/enemy/stage1/bandit_dead.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bandit_fire_effect", "image/enemy/stage1/bandit_fire_effect.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bandit_gun", "image/enemy/stage1/bandit_gun.bmp", 400, 50, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bandit_hurt", "image/enemy/stage1/bandit_hurt.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bandit_idle", "image/enemy/stage1/bandit_idle.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bandit_walk", "image/enemy/stage1/bandit_walk.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("bigbandit_dash", "image/enemy/stage1/bigbandit_dash.bmp", 360, 120, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigbandit_dead", "image/enemy/stage1/bigbandit_dead.bmp", 540, 120, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigbandit_fire", "image/enemy/stage1/bigbandit_fire.bmp", 120, 120, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigbandit_gun", "image/enemy/stage1/bigbandit_gun.bmp", 528, 66, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigbandit_hurt", "image/enemy/stage1/bigbandit_hurt.bmp", 180, 120, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigbandit_idle", "image/enemy/stage1/bigbandit_idle.bmp", 360, 120, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bigbandit_portrait", "image/enemy/stage1/bigbandit_portrait.bmp", 800, 425, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigbandit_walk", "image/enemy/stage1/bigbandit_walk.bmp", 480, 120, 8, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("bigmaggot_dead", "image/enemy/stage1/bigmaggot_dead.bmp", 448, 128, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigmaggot_hurt", "image/enemy/stage1/bigmaggot_hurt.bmp", 192, 128, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigmaggot_idle", "image/enemy/stage1/bigmaggot_idle.bmp", 384, 128, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigmaggot_burrow", "image/enemy/stage1/bigmaggot_burrow.bmp", 768, 128, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigmaggot_appear", "image/enemy/stage1/bigmaggot_appear.bmp", 448, 128, 7, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("greenmaggot_dead", "image/enemy/stage1/greenmaggot_dead.bmp", 192, 64, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenmaggot_hurt", "image/enemy/stage1/greenmaggot_hurt.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenmaggot_idle", "image/enemy/stage1/greenmaggot_idle.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("maggotnest_dead", "image/enemy/stage1/maggotnest_dead.bmp", 128, 128, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("maggotnest_hurt", "image/enemy/stage1/maggotnest_hurt.bmp", 192, 128, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("maggotnest_idle", "image/enemy/stage1/maggotnest_idle.bmp", 256, 128, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("maggot_dead", "image/enemy/stage1/maggot_dead.bmp", 192, 64, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("maggot_hurt", "image/enemy/stage1/maggot_hurt.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("maggot_idle", "image/enemy/stage1/maggot_idle.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("scolpion_bullet", "image/enemy/stage1/scolpion_bullet.bmp", 512, 32, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("scolpion_bullet_effect", "image/enemy/stage1/scolpion_bullet_effect.bmp", 144, 48, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("scolpion_dead", "image/enemy/stage1/scolpion_dead.bmp", 576, 192, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("scolpion_fire", "image/enemy/stage1/scolpion_fire.bmp", 192, 192, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("scolpion_hurt", "image/enemy/stage1/scolpion_hurt.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("scolpion_idle", "image/enemy/stage1/scolpion_idle.bmp", 1344, 192, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("scolpion_walk", "image/enemy/stage1/scolpion_walk.bmp", 576, 192, 6, 2, true, RGB(255, 0, 255));

	//stage2
	IMAGEMANAGER->addFrameImage("bigrat_attack", "image/enemy/stage2/bigrat_attack.bmp", 640, 192, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigrat_dead", "image/enemy/stage2/bigrat_dead.bmp", 576, 192, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigrat_fire", "image/enemy/stage2/bigrat_fire.bmp", 192, 192, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigrat_hurt", "image/enemy/stage2/bigrat_hurt.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigrat_idle", "image/enemy/stage2/bigrat_idle.bmp", 384, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigrat_walk", "image/enemy/stage2/bigrat_walk.bmp", 768, 192, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("frog_dead", "image/enemy/stage2/frog_dead.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("frog_explode", "image/enemy/stage2/frog_explode.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("frog_hurt", "image/enemy/stage2/frog_hurt.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("frog_idle", "image/enemy/stage2/frog_idle.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("frog_walk", "image/enemy/stage2/frog_walk.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gator_bullet1", "image/enemy/stage2/gator_bullet1.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gator_dead", "image/enemy/stage2/gator_dead.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gator_gun", "image/enemy/stage2/gator_gun.bmp", 320, 40, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gator_hurt", "image/enemy/stage2/gator_hurt.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gator_idle", "image/enemy/stage2/gator_idle.bmp", 384, 96, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gator_walk", "image/enemy/stage2/gator_walk.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenfrog_dead", "image/enemy/stage2/greenfrog_dead.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenfrog_hurt", "image/enemy/stage2/greenfrog_hurt.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenfrog_idle", "image/enemy/stage2/greenfrog_idle.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenfrog_walk", "image/enemy/stage2/greenfrog_walk.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenrat_dead", "image/enemy/stage2/greenrat_dead.bmp", 432, 96, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenrat_hurt", "image/enemy/stage2/greenrat_hurt.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenrat_idle", "image/enemy/stage2/greenrat_idle.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenrat_walk", "image/enemy/stage2/greenrat_walk.bmp", 576, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rat_dead", "image/enemy/stage2/rat_dead.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rat_hurt", "image/enemy/stage2/rat_hurt.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rat_idle", "image/enemy/stage2/rat_idle.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rat_walk", "image/enemy/stage2/rat_walk.bmp", 575, 96, 6, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("shotgun1", "image/enemy/stage2/shotgun1.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shotgun2", "image/enemy/stage2/shotgun2.bmp", 32, 32, true, RGB(255, 0, 255));


	//stage3


	IMAGEMANAGER->addFrameImage("assassin_dead", "image/enemy/stage3/assassin_dead.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("assassin_fake", "image/enemy/stage3/assassin_fake.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("assassin_hurt", "image/enemy/stage3/assassin_hurt.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("assassin_idle", "image/enemy/stage3/assassin_idle.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("assassin_notice", "image/enemy/stage3/assassin_notice.bmp", 240, 48, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("assassin_walk", "image/enemy/stage3/assassin_walk.bmp", 298, 48, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("assassin_weapon", "image/enemy/stage3/assassin_weapon.bmp", 448, 56, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigdog_idle", "image/enemy/stage3/bigdog_idle.bmp", 1068, 248, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigdog_idle_hurt", "image/enemy/stage3/bigdog_idle_hurt.bmp", 356, 248, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigdog_sleep", "image/enemy/stage3/bigdog_sleep.bmp", 2324, 212, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigdog_spin", "image/enemy/stage3/bigdog_spin.bmp", 392, 120, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigdog_spin_hurt", "image/enemy/stage3/bigdog_spin_hurt.bmp", 392, 120, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigdog_spinend", "image/enemy/stage3/bigdog_spinend.bmp", 392, 240, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bigdog_portrait", "image/enemy/stage3/bigdog_portrait.bmp", 800, 459, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("firetrap", "image/enemy/stage3/firetrap.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("raven_dead", "image/enemy/stage3/raven_dead.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("raven_fly", "image/enemy/stage3/raven_fly.bmp", 640, 256, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("raven_hurt", "image/enemy/stage3/raven_hurt.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("raven_idle", "image/enemy/stage3/raven_idle.bmp", 432, 96, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("raven_land", "image/enemy/stage3/raven_land.bmp", 512, 256, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("raven_lift", "image/enemy/stage3/raven_lift.bmp", 640, 256, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("raven_walk", "image/enemy/stage3/raven_walk.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("salamander_bullet", "image/enemy/stage3/salamander_bullet.bmp", 224, 32, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("salamander_fire", "image/enemy/stage3/salamander_fire.bmp", 192, 192, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("salamander_dead", "image/enemy/stage3/salamander_dead.bmp", 768, 192, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("salamander_hurt", "image/enemy/stage3/salamander_hurt.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("salamander_idle", "image/enemy/stage3/salamander_idle.bmp", 672, 192, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("salamander_walk", "image/enemy/stage3/salamander_walk.bmp", 768, 192, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sniper_bullet", "image/enemy/stage3/sniper_bullet.bmp", 512, 32, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sniper_dead", "image/enemy/stage3/sniper_dead.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sniper_hurt", "image/enemy/stage3/sniper_hurt.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sniper_idle", "image/enemy/stage3/sniper_idle.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sniper_walk", "image/enemy/stage3/sniper_walk.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));


}

void enemyManager::remove()
{
	_mvEnemy.clear();
	_showEnemy.clear();
}

void enemyManager::addEnemys(string strKey, ENEMYTYPE enemyType, int x, int y)
{
	mviEnemy _miter;
	vector<enemy*> _vtemp;
	bool isfound = false;
	enemy* temp;

	//들어온 enemyType으로 enemy 생성
	switch (enemyType)
	{
	case BIGBANDIT:
		temp = new bigBandit;
		break;
	case BANDIT:
		temp = new bandit;
		break;
	case BIGMAGGOT:
		temp = new bigMaggot;
		break;
	case MAGGOT:
		temp = new maggot;
		break;
	case GREENMAGGOT:
		temp = new greenMaggot;
		break;
	case SCOLPION:
		temp = new scolpion;
		break;
	case MAGGOTNEST:
		temp = new maggotNest;
		break;
	case BIGRAT:
		temp = new bigRat;
		break;
	case RAT:
		temp = new rat;
		break;
	case GREENRAT:
		temp = new greenRat;
		break;
	case FROG:
		temp = new frog;
		break;
	case GREENFROG:
		temp = new greenFrog;
		break;
	case GATOR:
		temp = new gator;
		break;
	case BIGDOG:
		temp = new bigDog;
		break;
	case ASSASSIN:
		temp = new assassin;
		break;
	case RAVEN:
		temp = new raven;
		break;
	case SALAMADER:
		temp = new salamander;
		break;
	case SNIPER:
		temp = new sniper;
		break;
	default:
		temp = new bandit;
		break;
	}
	temp->init(x, y);

	//map 안에서 strKey값으로 vector를 찾았을 때
	for (_miter = _mvEnemy.begin(); _miter != _mvEnemy.end();) {
		if (_miter->first == strKey) {
			(_mvEnemy.find(strKey)->second).push_back(temp);
			isfound = true;
			break;
		}
	}
	//못찾으면 새로 strKey값으로 vector를 추가하여 map에 추가
	if (!isfound) {
		_vtemp.push_back(temp);
		_mvEnemy.insert(pair<string, vEnemy>(strKey, _vtemp));
	}
}

void enemyManager::deleteEnemys(string strKey, int x, int y)
{
	mviEnemy _miter;
	vEnemy _vtemp;
	viEnemy _viter;

	//strKey에 해당하는 vector를 찾고
	for (_miter = _mvEnemy.begin(); _miter != _mvEnemy.end(); ++_miter) {
		if (_miter->first == strKey) {

			for (_viter = _miter->second.begin(); _viter != _miter->second.end();) {
				//좌표와 동일하면
				if ((int)(*_viter)->getInfo().pt.x == x && (int)(*_viter)->getInfo().pt.y == y) {
					//vector에서 지워줌
					_viter = _miter->second.erase(_viter);
				}
				else {
					++_viter;
				}
			}
			break;
		}
	}

}

vector<enemy*> enemyManager::getEnemys(string strKey)
{
	mviEnemy _miter;
	vector<enemy*> _vtemp;
	for (_miter = _mvEnemy.begin(); _miter != _mvEnemy.end(); ++_miter) {
		if (_miter->first == strKey) {
			_vtemp = _miter->second;
			break;
		}
	}
	return _vtemp;
}

void enemyManager::createMaggot(POINT pt)
{
	for (int i = 0; i < 6; i++)
	{
		enemy* temp;
		temp = new maggot;
		temp->init(pt.x + RND->getFromFloatTo(-30, 30), pt.y + RND->getFromFloatTo(-30, 30));
		_showEnemy.push_back(temp);
	}
	//cout << "showenemyVector size = " << _showEnemy.size() << endl;
}

void enemyManager::createGreenMaggot(POINT pt)
{
	for (int i = 0; i < 6; i++)
	{
		enemy* temp;
		temp = new greenMaggot;
		temp->init(pt.x + RND->getFromFloatTo(-30, 30), pt.y + RND->getFromFloatTo(-30, 30));
		_showEnemy.push_back(temp);
	}
	//cout << "showenemyVector size = " << _showEnemy.size() << endl;
}

void enemyManager::createGreenRat(POINT pt)
{
	for (int i = 0; i < 4; i++)
	{
		enemy* temp;
		temp = new greenRat;
		temp->init(pt.x + RND->getFromFloatTo(-40, 40), pt.y + RND->getFromFloatTo(-40, 40));
		_showEnemy.push_back(temp);
	}
}


void enemyManager::setShowEnemyVector(string strKey)
{
	_showEnemy = getEnemys(strKey);
}

void enemyManager::createRandomEnemyVector()
{

	//현재 타일의 열린 곳을 set
	MAPMANAGER->setOpenTiles();
	//보여주기용 에너미 벡터를 모두 비운다.
	clearShowEnemyVector();

	//해당 라운드를 받아, Boss 를 1마리 만들어 준다.
	//0 : BigBandit
	//13: BigDog

	if (MAPMANAGER->getStage_first() == 0 && MAPMANAGER->getStage_second() == 1) {
		enemy* boss_temp = new bigBandit;
		boss_temp->init(
			MAPMANAGER->getOpenTiles()[RND->getInt(MAPMANAGER->getOpenTiles().size())].x,
			MAPMANAGER->getOpenTiles()[RND->getInt(MAPMANAGER->getOpenTiles().size())].y);
		_showEnemy.push_back(boss_temp);
	}
	else if (MAPMANAGER->getStage_first() == 2 && MAPMANAGER->getStage_second() == 1) {
		enemy* boss_temp = new bigDog;
		boss_temp->init(
			MAPMANAGER->getOpenTiles()[RND->getInt(MAPMANAGER->getOpenTiles().size())].x,
			MAPMANAGER->getOpenTiles()[RND->getInt(MAPMANAGER->getOpenTiles().size())].y);
		_showEnemy.push_back(boss_temp);
	}


	//정해진 enemy count 만큼 에너미를 만든다
	for (int i = 0; i < MAPMANAGER->getEnemyCount(); ++i) {
		enemy* temp;
		ENEMYTYPE rndEnemy;

		//현재 스테이지를 받아와서 해당 스테이지에 맞는 에너미를 생성한다.
		switch (MAPMANAGER->getStage_first())
		{
		case 0:
			rndEnemy = (ENEMYTYPE)RND->getFromIntTo(1, 7);
			break;
		case 1:
			rndEnemy = (ENEMYTYPE)RND->getFromIntTo(7, 13);
			break;
		case 2:
			rndEnemy = (ENEMYTYPE)RND->getFromIntTo(14, 18);
			break;
		default:
			//예외 상태
			rndEnemy = (ENEMYTYPE)RND->getFromIntTo(0, 18);
			break;
		}

		//들어온 enemyType으로 enemy 생성
		switch (rndEnemy)
		{
		case BIGBANDIT:
			temp = new bigBandit;
			break;
		case BANDIT:
			temp = new bandit;
			break;
		case BIGMAGGOT:
			temp = new bigMaggot;
			break;
		case MAGGOT:
			temp = new maggot;
			break;
		case GREENMAGGOT:
			temp = new greenMaggot;
			break;
		case SCOLPION:
			temp = new scolpion;
			break;
		case MAGGOTNEST:
			temp = new maggotNest;
			break;
		case BIGRAT:
			temp = new bigRat;
			break;
		case RAT:
			temp = new rat;
			break;
		case GREENRAT:
			temp = new greenRat;
			break;
		case FROG:
			temp = new frog;
			break;
		case GREENFROG:
			temp = new greenFrog;
			break;
		case GATOR:
			temp = new gator;
			break;
		case BIGDOG:
			temp = new bigDog;
			break;
		case ASSASSIN:
			temp = new assassin;
			break;
		case RAVEN:
			temp = new raven;
			break;
		case SALAMADER:
			temp = new salamander;
			break;
		case SNIPER:
			temp = new sniper;
			break;
		default:
			temp = new bandit;
			break;
		}

		//open tile 중, random으로 index를 참조하여 타일의 중간값으로 에너미의 좌표를 지정해준다.
		temp->init(
			MAPMANAGER->getOpenTiles()[RND->getInt(MAPMANAGER->getOpenTiles().size())].x,
			MAPMANAGER->getOpenTiles()[RND->getInt(MAPMANAGER->getOpenTiles().size())].y);
		_showEnemy.push_back(temp);
	}
}

void enemyManager::removeEnemy(int i)
{
	_showEnemy.erase(_showEnemy.begin() + i);
}

void enemyManager::plantSkill()
{
	for (int i = 0; i < _showEnemy.size(); i++)
	{
		_showEnemy[i]->plantBulletCollision();
	}
}

bool enemyManager::checkShowEnemyVector()
{
	bool isAllDead = true;

	for (int i = 0; i < _showEnemy.size(); ++i) {
		if (_showEnemy[i]->getState() != E_DEAD) {
			isAllDead = false;
		}
	}

	return isAllDead;
}
