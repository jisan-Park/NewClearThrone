#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	//해당 라운드의 랜덤맵 생성
	MAPMANAGER->setRandomMap();
	//player 위치 시작점으로 설정
	PLAYERMANAGER->setPlayerPosition(MAPMANAGER->getStartPoint());
	//random enemy set
	ENEMYMANAGER->createRandomEnemyVector();

	//sound
	_sound1 = 0;
	_sound2 = 0;
	_sound3 = 0;

	return S_OK;
}

void gameScene::update()
{
	//pause
	if (KEYMANAGER->isOnceKeyDown(VK_TAB)) {
		if (GAMEMANAGER->getIsPaused()) {
			GAMEMANAGER->setIsPaused(false);
			GAMEMANAGER->setIsSetting(false);
		}
		else {
			GAMEMANAGER->setIsPaused(true);
		}
	}

	//paused 면 update안함
	if (GAMEMANAGER->getIsPaused()) {
		if (GAMEMANAGER->getIsSetting()) {
			GAMEMANAGER->volumeUpdate();
		}
		else {
			GAMEMANAGER->pauseUpdate();
		}
	}
	else {
		for (enemy* e : ENEMYMANAGER->getShowEnemyVector()) {
			//각 에너미의 update
			e->update();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_BACK)) {
			SCENEMANAGER->changeScene("메인메뉴씬");
		}

		//player update
		PLAYERMANAGER->update();

		//map update
		//MAPMANAGER->autoTile();

		//player 기준으로 camera set
		CAMERAMANAGER->setCameraPoint(
			PLAYERMANAGER->getPlayer()->getPt().x,
			PLAYERMANAGER->getPlayer()->getPt().y);
		//mouse update
		CAMERAMANAGER->update();

		if (MAPMANAGER->getStage_first() == 0 && _sound1 == 0)
		{
			SOUNDMANAGER->play("스테이지1", (GAMEMANAGER->getSfxVolume() / 100.0f)*1.0f);
			_sound1++;
		}
		else if (MAPMANAGER->getStage_first() == 1 && _sound2 == 0 )
		{
			SOUNDMANAGER->play("스테이지2", (GAMEMANAGER->getSfxVolume() / 100.0f)*1.0f);
			_sound2++;
		}
		else if (MAPMANAGER->getStage_first() == 2 && _sound3 == 0)
		{
			SOUNDMANAGER->play("스테이지2", (GAMEMANAGER->getSfxVolume() / 100.0f)*1.0f);
			_sound3++;
		}

	}
}

void gameScene::release()
{
}

void gameScene::render()
{
	//map tile render
	MAPMANAGER->strectchSceneRender(getMapDC());

	//player render
	PLAYERMANAGER->render(getMapDC());

	//enemy render
	for (enemy* e : ENEMYMANAGER->getShowEnemyVector()) {
		//각 에너미의 update
		e->render(getMapDC());
	}

	//map wall rect render
	if (KEYMANAGER->isToggleKey(VK_F2)) {
		MAPMANAGER->RectRender(getMapDC());
	}


	//마우스 포인터 render
	RECT _mouse = RectMakeCenter(CAMERAMANAGER->getMousePoint().x, CAMERAMANAGER->getMousePoint().y, 40, 40);
	IMAGEMANAGER->findImage("mouse_aim")->render(getMapDC(), _mouse.left, _mouse.top);

	//mapBuffer 에 그려져 있는 내용들을 memDC에 옮김
	_mapBuffer->stretchRender(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, CAMERAMANAGER->getSizeX(), CAMERAMANAGER->getSizeY());

	//pause render
	GAMEMANAGER->pauseRender(getMemDC());
}
