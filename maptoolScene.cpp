#include "stdafx.h"
#include "maptoolScene.h"

HRESULT maptoolScene::init()
{
	setImage();
	//setter
	MAPMANAGER->setWidthCount(12);
	MAPMANAGER->setHeightCount(10);
	MAPMANAGER->setSize(64);
	//MAPMANAGER->setShowTileMemory();
	//set 된 값으로 그릴 maptile set
	MAPMANAGER->updateTileIndex();
	return S_OK;
}

void maptoolScene::update()
{
	KEYANIMANAGER->update();
	keyupdate();
	MAPMANAGER->moveIndex();
	MAPMANAGER->setMap();
	MAPMANAGER->autoTile();
}

void maptoolScene::release()
{
}

void maptoolScene::render()
{
	IMAGEMANAGER->findImage("black")->render(getMemDC());

	//tag Button
	for (int i = 0; i < 6; ++i) {
		selectTile[i].info.img->alphaRender(getMemDC(), selectTile[i].info.rc.left, selectTile[i].info.rc.top,selectTile[i].alpha);
	}
	for (int i = 0; i < 7; ++i) {
		selectBtn[i].info.img->alphaRender(getMemDC(), selectBtn[i].info.rc.left, selectBtn[i].info.rc.top, selectBtn[i].alpha);
	}

	//MAPMANAGER->mapRender(getMemDC());

	//맵버퍼에 타일을 그려 놓는다
	MAPMANAGER->stretchMapRender(getMapDC());
	//맵버퍼에 그려놓은 타일을 700x700 사이즈에 맞춰서 stretchRender
	_mapBuffer->stretchRender(getMemDC(),0,0,768,640,
		MAPMANAGER->getPoint().x * TILESIZE,
		MAPMANAGER->getPoint().y * TILESIZE,
		MAPMANAGER->getWidthCount()*TILESIZE,
		MAPMANAGER->getHeightCount()*TILESIZE);

	MAPMANAGER->mapToolRender(getMemDC());
}


void maptoolScene::setImage()
{

	IMAGEMANAGER->addImage("tile","image/Scene/maptool/tile.bmp",80,40,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("wall", "image/Scene/maptool/wall.bmp", 80, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("object", "image/Scene/maptool/object.bmp", 80, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemy", "image/Scene/maptool/enemy.bmp", 80, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player", "image/Scene/maptool/player.bmp", 80, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss", "image/Scene/maptool/boss.bmp",80,40,true,RGB(255,0,255));

	IMAGEMANAGER->addImage("save_btn", "image/Scene/maptool/save.bmp", 77, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("load_btn", "image/Scene/maptool/load.bmp", 74, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("quit_btn", "image/Scene/maptool/quit.bmp", 66, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("eraser_btn", "image/Scene/maptool/erase.bmp", 80, 40, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("random1_btn", "image/Scene/maptool/stage1.bmp", 125, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("random2_btn", "image/Scene/maptool/stage2.bmp", 125, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("random3_btn", "image/Scene/maptool/stage3.bmp", 125, 20, true, RGB(255, 0, 255));


	selectTile[0].info.img = new image;
	selectTile[1].info.img = new image;
	selectTile[2].info.img = new image;
	selectTile[3].info.img = new image;
	selectTile[4].info.img = new image;
	selectTile[5].info.img = new image;

	selectBtn[0].info.img = new image;
	selectBtn[1].info.img = new image;
	selectBtn[2].info.img = new image;
	selectBtn[3].info.img = new image;
	selectBtn[4].info.img = new image;
	selectBtn[5].info.img = new image;
	selectBtn[6].info.img = new image;

	selectTile[0].info.img = IMAGEMANAGER->findImage("tile");
	selectTile[1].info.img = IMAGEMANAGER->findImage("wall");
	selectTile[2].info.img = IMAGEMANAGER->findImage("object");
	selectTile[3].info.img = IMAGEMANAGER->findImage("enemy");
	selectTile[4].info.img = IMAGEMANAGER->findImage("boss");
	selectTile[5].info.img = IMAGEMANAGER->findImage("player");

	selectBtn[0].info.img = IMAGEMANAGER->findImage("save_btn");
	selectBtn[1].info.img = IMAGEMANAGER->findImage("load_btn");
	selectBtn[2].info.img = IMAGEMANAGER->findImage("quit_btn");
	selectBtn[3].info.img = IMAGEMANAGER->findImage("eraser_btn");
	selectBtn[4].info.img = IMAGEMANAGER->findImage("random1_btn");
	selectBtn[5].info.img = IMAGEMANAGER->findImage("random2_btn");
	selectBtn[6].info.img = IMAGEMANAGER->findImage("random3_btn");

	selectTile[0].info.rc = RectMakeCenter(WINSIZEX - 400 - selectTile[0].info.img->getWidth() / 2, selectTile[0].info.img->getHeight() / 2, selectTile[0].info.img->getWidth(), selectTile[0].info.img->getHeight());
	selectTile[1].info.rc = RectMakeCenter(WINSIZEX - 320 - selectTile[1].info.img->getWidth() / 2, selectTile[1].info.img->getHeight() / 2, selectTile[1].info.img->getWidth(), selectTile[1].info.img->getHeight());
	selectTile[2].info.rc = RectMakeCenter(WINSIZEX - 240 - selectTile[2].info.img->getWidth() / 2, selectTile[2].info.img->getHeight() / 2, selectTile[2].info.img->getWidth(), selectTile[2].info.img->getHeight());
	selectTile[3].info.rc = RectMakeCenter(WINSIZEX - 160 - selectTile[3].info.img->getWidth() / 2, selectTile[3].info.img->getHeight() / 2, selectTile[3].info.img->getWidth(), selectTile[3].info.img->getHeight());
	selectTile[4].info.rc = RectMakeCenter(WINSIZEX - 80 - selectTile[4].info.img->getWidth() / 2, selectTile[4].info.img->getHeight() / 2, selectTile[4].info.img->getWidth(), selectTile[4].info.img->getHeight());
	selectTile[5].info.rc = RectMakeCenter(WINSIZEX - selectTile[5].info.img->getWidth() / 2, selectTile[5].info.img->getHeight() / 2, selectTile[5].info.img->getWidth(), selectTile[5].info.img->getHeight());

	selectBtn[0].info.rc = RectMakeCenter(920, WINSIZEY - 10 - selectBtn[0].info.img->getHeight() / 2, selectBtn[0].info.img->getWidth(), selectBtn[0].info.img->getHeight());
	selectBtn[1].info.rc = RectMakeCenter(1060, WINSIZEY - 10 - selectBtn[1].info.img->getHeight() / 2, selectBtn[1].info.img->getWidth(), selectBtn[1].info.img->getHeight());
	selectBtn[2].info.rc = RectMakeCenter(1200, WINSIZEY - 10 - selectBtn[2].info.img->getHeight() / 2, selectBtn[2].info.img->getWidth(), selectBtn[2].info.img->getHeight());
	selectBtn[3].info.rc = RectMakeCenter(1060, WINSIZEY - 100, selectTile[4].info.img->getWidth(), selectTile[4].info.img->getHeight());
	selectBtn[4].info.rc = RectMakeCenter(920, WINSIZEY - 160, 120, 25);
	selectBtn[5].info.rc = RectMakeCenter(1060, WINSIZEY - 160, 120, 25);
	selectBtn[6].info.rc = RectMakeCenter(1200, WINSIZEY - 160, 120, 25);

	for (int i = 0; i < 6; ++i) {
		selectTile[i].alpha = 100;
	}
	for (int i = 0; i < 4; ++i) {
		selectBtn[i].alpha = 100;
	}
}

void maptoolScene::keyupdate()
{

	//setAlpha
	for (int i = 0; i < 6; ++i) {
		if (PtInRect(&selectTile[i].info.rc, _ptMouse)) {
			selectTile[i].alpha = 255;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				switch (i)
				{
				case 0:
					MAPMANAGER->setSelectBtn(DrawTerrain);
					break;
				case 1:
					MAPMANAGER->setSelectBtn(DrawWall);
					break;
				case 2:
					MAPMANAGER->setSelectBtn(DrawObj);
					break;
				case 3:
					MAPMANAGER->setSelectBtn(DrawEnemy);
					break;
				case 4:
					MAPMANAGER->setSelectBtn(DrawBoss);
					break;
				case 5:
					MAPMANAGER->setSelectBtn(DrawPlayer);
				default:
					break;
				}
			}
		}
		else {
			selectTile[i].alpha = 100;
		}
	}
	for (int i = 0; i < 7; ++i) {
		if (PtInRect(&selectBtn[i].info.rc, _ptMouse)) {
			selectBtn[i].alpha = 255;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				switch (i)
				{
				case 0:
					MAPMANAGER->save();
					break;
				case 1:
					MAPMANAGER->load();
					break;
				case 2:
					SCENEMANAGER->changeScene("메인메뉴씬");
					break;
				case 3:
					MAPMANAGER->setSelectBtn(Eraser);
					MAPMANAGER->eraser();
					break;
				case 4:
					MAPMANAGER->setRandomStage(0);
					MAPMANAGER->random();
					break;
				case 5:
					MAPMANAGER->setRandomStage(1);
					MAPMANAGER->random();
					break;
				case 6:
					MAPMANAGER->setRandomStage(2);
					MAPMANAGER->random();
					break;
				default:
					break;
				}
			}
		}
		else {
			selectBtn[i].alpha = 100;
		}
	}
}