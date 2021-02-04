#include "stdafx.h"
#include "customScene.h"

HRESULT customScene::init()
{
	//maptool set
	MAPMANAGER->load("saveMap1.bmp");
	mouse = RectMake(0,0,64,64);
	return S_OK;
}

void customScene::update()
{
	for (enemy* e : ENEMYMANAGER->getEnemys("custom")) {
		//각 에너미의 update
		e->update();
	}
		

	if (KEYMANAGER->isOnceKeyDown(VK_BACK)) {
		SCENEMANAGER->changeScene("메인메뉴씬");
	}
	PLAYERMANAGER->update();

	//player 기준으로 camera set
	CAMERAMANAGER->setCameraPoint(
		PLAYERMANAGER->getPlayer()->getPt().x,
		PLAYERMANAGER->getPlayer()->getPt().y);
	

	CAMERAMANAGER->update();

}

void customScene::release()
{
}

void customScene::render()
{
	//타일
	/*MAPMANAGER->strectchSceneRender(getMemDC());
	PLAYERMANAGER->render(getMemDC());
	Rectangle(getMemDC(), mouse);*/

	MAPMANAGER->strectchSceneRender(getMapDC());
	PLAYERMANAGER->render(getMapDC());

	for (enemy* e : ENEMYMANAGER->getEnemys("custom")) {
		//각 에너미의 update
		e->render(getMapDC());
	}

	Rectangle(getMapDC(), mouse);
	MAPMANAGER->RectRender(getMapDC());

	_mapBuffer->stretchRender(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, CAMERAMANAGER->getSizeX(), CAMERAMANAGER->getSizeY());
}
