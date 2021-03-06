#include "stdafx.h"
#include "customScene.h"

HRESULT customScene::init()
{
	//maptool set
	MAPMANAGER->load("saveMap1.bmp");
	ENEMYMANAGER->setShowEnemyVector("custom");
	BULLETMANAGER->init();
	GAMEMANAGER->setUIImage();
	return S_OK;
}

void customScene::update()
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
		BULLETMANAGER->update();

		//만약 enemyVector가 비어있다면
		if (ENEMYMANAGER->checkShowEnemyVector()) {
			MAPMANAGER->createPortal();
		}
		//포탈과 충돌이 일어나면 카드선택씬으로 이동
		MAPMANAGER->collisionPortal();

		for (enemy* e : ENEMYMANAGER->getShowEnemyVector()) {
			//각 에너미의 update
			e->update();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_BACK)) {
			SCENEMANAGER->changeScene("메인메뉴씬");
		}

		//player update
		PLAYERMANAGER->update();
		GAMEMANAGER->updateUI();
		//item update
		ITEMMANAGER->update();

		//player 기준으로 camera set
		CAMERAMANAGER->setCameraPoint(
			PLAYERMANAGER->getPlayer()->getPt().x,
			PLAYERMANAGER->getPlayer()->getPt().y);
		//mouse update
		EFFECTMANAGER->update();
		CAMERAMANAGER->update();
		MAPMANAGER->autoTile();
	}
}

void customScene::release()
{
}

void customScene::render()
{
	//map tile render

	MAPMANAGER->strectchSceneRender(getMapDC());

	//item render
	ITEMMANAGER->render(getMapDC());

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
		Rectangle(getMapDC(),PLAYERMANAGER->getPlayer()->getRect().left, PLAYERMANAGER->getPlayer()->getRect().top, PLAYERMANAGER->getPlayer()->getRect().right, PLAYERMANAGER->getPlayer()->getRect().bottom);
	}
	//만약 enemyVector가 비어있다면
	if (ENEMYMANAGER->checkShowEnemyVector()) {
		MAPMANAGER->renderPortal(getMapDC());
	}
	
	//마우스 포인터 render
	RECT _mouse = RectMakeCenter(CAMERAMANAGER->getMousePoint().x, CAMERAMANAGER->getMousePoint().y, 40, 40);
	IMAGEMANAGER->findImage("mouse_aim")->render(getMapDC(), _mouse.left, _mouse.top);
	BULLETMANAGER->render(getMapDC());

	//effectRender getMapDC();
	EFFECTMANAGER->render();

	//mapBuffer 에 그려져 있는 내용들을 memDC에 옮김
	_mapBuffer->stretchRender(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, CAMERAMANAGER->getSizeX(), CAMERAMANAGER->getSizeY());
	
	//pause render
	GAMEMANAGER->pauseRender(getMemDC());
	//ui render
	GAMEMANAGER->UIRender(getMemDC());
}
