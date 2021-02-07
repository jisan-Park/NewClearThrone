#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	//�ش� ������ ������ ����
	MAPMANAGER->setRandomMap();
	//player ��ġ ���������� ����
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
		for (enemy* e : ENEMYMANAGER->getShowEnemyVector()) {
			//�� ���ʹ��� update
			e->update();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_BACK)) {
			SCENEMANAGER->changeScene("���θ޴���");
		}

		//player update
		PLAYERMANAGER->update();

		//map update
		//MAPMANAGER->autoTile();

		//player �������� camera set
		CAMERAMANAGER->setCameraPoint(
			PLAYERMANAGER->getPlayer()->getPt().x,
			PLAYERMANAGER->getPlayer()->getPt().y);
		//mouse update
		CAMERAMANAGER->update();
		MAPMANAGER->autoTile();


		//SOUND
		if (MAPMANAGER->getStage_first() == 0 && _sound1 == 0)
		{
			SOUNDMANAGER->stop("��������1");
			SOUNDMANAGER->stop("��������2");
			SOUNDMANAGER->stop("��������3");
			SOUNDMANAGER->stop("���θ޴�");
			SOUNDMANAGER->stop("ĳ���ͼ���");
		
			SOUNDMANAGER->play("��������1", GAMEMANAGER->getMusicVolume() * GAMEMANAGER->getMasterVolume());
			_sound1++;
		}
		else if (MAPMANAGER->getStage_first() == 1 && _sound2 == 0 )
		{
			SOUNDMANAGER->stop("��������1");
			SOUNDMANAGER->stop("��������2");
			SOUNDMANAGER->stop("��������3");
			SOUNDMANAGER->stop("���θ޴�");
			SOUNDMANAGER->stop("ĳ���ͼ���");

			SOUNDMANAGER->play("��������2", GAMEMANAGER->getMusicVolume() * GAMEMANAGER->getMasterVolume());
			_sound2++;
		}
		else if (MAPMANAGER->getStage_first() == 2 && _sound3 == 0)
		{
			SOUNDMANAGER->stop("��������1");
			SOUNDMANAGER->stop("��������2");
			SOUNDMANAGER->stop("��������3");
			SOUNDMANAGER->stop("���θ޴�");
			SOUNDMANAGER->stop("ĳ���ͼ���");

			SOUNDMANAGER->play("��������3", GAMEMANAGER->getMusicVolume() * GAMEMANAGER->getMasterVolume());
			_sound3++;
		}

	}

	EFFECTMANAGER->update();
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
		//�� ���ʹ��� update
		e->render(getMapDC());
	}

	//map wall rect render
	if (KEYMANAGER->isToggleKey(VK_F2)) {
		MAPMANAGER->RectRender(getMapDC());
	}


	//���콺 ������ render
	RECT _mouse = RectMakeCenter(CAMERAMANAGER->getMousePoint().x, CAMERAMANAGER->getMousePoint().y, 40, 40);
	IMAGEMANAGER->findImage("mouse_aim")->render(getMapDC(), _mouse.left, _mouse.top);

	//mapBuffer �� �׷��� �ִ� ������� memDC�� �ű�
	_mapBuffer->stretchRender(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, CAMERAMANAGER->getSizeX(), CAMERAMANAGER->getSizeY());

	//pause render
	GAMEMANAGER->pauseRender(getMemDC());
}
