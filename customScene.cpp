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

	//paused �� update����
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

		//���� enemyVector�� ����ִٸ�
		if (ENEMYMANAGER->checkShowEnemyVector()) {
			MAPMANAGER->createPortal();
		}
		//��Ż�� �浹�� �Ͼ�� ī�弱�þ����� �̵�
		MAPMANAGER->collisionPortal();

		for (enemy* e : ENEMYMANAGER->getShowEnemyVector()) {
			//�� ���ʹ��� update
			e->update();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_BACK)) {
			SCENEMANAGER->changeScene("���θ޴���");
		}

		//player update
		PLAYERMANAGER->update();
		GAMEMANAGER->updateUI();
		//item update
		ITEMMANAGER->update();

		//player �������� camera set
		CAMERAMANAGER->setCameraPoint(
			PLAYERMANAGER->getPlayer()->getPt().x,
			PLAYERMANAGER->getPlayer()->getPt().y);
		//mouse update
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
		//�� ���ʹ��� update
		e->render(getMapDC());
	}

	//map wall rect render
	if (KEYMANAGER->isToggleKey(VK_F2)) {
		MAPMANAGER->RectRender(getMapDC());
		Rectangle(getMapDC(),PLAYERMANAGER->getPlayer()->getRect().left, PLAYERMANAGER->getPlayer()->getRect().top, PLAYERMANAGER->getPlayer()->getRect().right, PLAYERMANAGER->getPlayer()->getRect().bottom);
	}
	//���� enemyVector�� ����ִٸ�
	if (ENEMYMANAGER->checkShowEnemyVector()) {
		MAPMANAGER->renderPortal(getMapDC());
	}

	//���콺 ������ render
	RECT _mouse = RectMakeCenter(CAMERAMANAGER->getMousePoint().x, CAMERAMANAGER->getMousePoint().y, 40, 40);
	IMAGEMANAGER->findImage("mouse_aim")->render(getMapDC(), _mouse.left, _mouse.top);
	BULLETMANAGER->render(getMapDC());
	//mapBuffer �� �׷��� �ִ� ������� memDC�� �ű�
	_mapBuffer->stretchRender(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, CAMERAMANAGER->getSizeX(), CAMERAMANAGER->getSizeY());

	//pause render
	GAMEMANAGER->pauseRender(getMemDC());
	//ui render
	GAMEMANAGER->UIRender(getMemDC());
}
