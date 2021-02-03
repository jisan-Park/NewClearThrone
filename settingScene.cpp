#include "stdafx.h"
#include "settingScene.h"

HRESULT settingScene::init()
{
	setImage();
	return S_OK;
}

void settingScene::update()
{
	if (PtInRect(&back.info.rc, _ptMouse)) {
		back.alpha = 255;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SCENEMANAGER->changeScene("메인메뉴씬");
		}
	}
	else {
		back.alpha = 100;
	}

	KEYANIMANAGER->update();
}

void settingScene::release()
{
}

void settingScene::render()
{
	IMAGEMANAGER->findImage("background")->aniRender(getMemDC(), 0, 0, KEYANIMANAGER->findAnimation("backgroundAnimation"));
	//volume name
	IMAGEMANAGER->findImage("master_volume")->render(getMemDC(), WINSIZEX / 8, WINSIZEY / 2 - 100);
	IMAGEMANAGER->findImage("music_volume")->render(getMemDC(), WINSIZEX / 8, WINSIZEY / 2);
	IMAGEMANAGER->findImage("sfx_volume")->render(getMemDC(), WINSIZEX / 8, WINSIZEY / 2 + 100);

	//volume front Bar
	master.frontBar->render(getMemDC(), master.rc.left, master.rc.top, 0, 0, ((master.width / 100.0f) * master.backBar->getWidth()), master.backBar->getHeight());
	music.frontBar->render(getMemDC(), music.rc.left, music.rc.top, 0, 0, ((music.width / 100.0f) * music.backBar->getWidth()), music.backBar->getHeight());
	sfx.frontBar->render(getMemDC(), sfx.rc.left, sfx.rc.top, 0, 0, ((sfx.width / 100.0f) * sfx.backBar->getWidth()), sfx.backBar->getHeight());

	//volume back Bar
	master.backBar->render(getMemDC(), master.rc.left, master.rc.top);
	music.backBar->render(getMemDC(), music.rc.left, music.rc.top);
	sfx.backBar->render(getMemDC(), sfx.rc.left, sfx.rc.top);

	//volume button
	master.button->render(getMemDC(), master.rc.left + ((master.width / 100.0f) * master.backBar->getWidth()), master.rc.top);
	music.button->render(getMemDC(), music.rc.left + ((music.width / 100.0f) * music.backBar->getWidth()), music.rc.top);
	sfx.button->render(getMemDC(), sfx.rc.left + ((sfx.width / 100.0f) * sfx.backBar->getWidth()), sfx.rc.top);

	//back button
	back.info.img->alphaRender(getMemDC(), back.info.rc.left, back.info.rc.top, back.alpha);

	//마우스 포인터 render
	RECT _mouse = RectMakeCenter(_ptMouse.x, _ptMouse.y, 40, 40);
	IMAGEMANAGER->findImage("mouse_aim")->render(getMemDC(), _mouse.left, _mouse.top);
}

void settingScene::setImage()
{
	IMAGEMANAGER->addImage("back", "image/scene/back.bmp", 74, 25, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("master_volume", "image/scene/settingScene/master_volume.bmp", 238, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("music_volume", "image/scene/settingScene/music_volume.bmp", 213, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sfx_volume", "image/scene/settingScene/sfx_volume.bmp", 183, 25, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("volumeBackBar", "image/scene/settingScene/volumeBackBar.bmp", 300, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("volumeFrontBar", "image/scene/settingScene/volumeFrontBar.bmp", 300, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("volumeButton", "image/scene/settingScene/volumeButton.bmp", 10, 50, true, RGB(255, 0, 255));

	back.info.img = new image;
	back.info.img = IMAGEMANAGER->findImage("back");
	back.info.x = WINSIZEX - 100;
	back.info.y = WINSIZEY - 100;
	back.alpha = 100;
	back.info.rc = RectMakeCenter(back.info.x, back.info.y, back.info.img->getWidth(), back.info.img->getHeight());

	master.backBar = new image;
	master.frontBar = new image;
	master.button = new image;
	master.backBar = IMAGEMANAGER->findImage("volumeBackBar");
	master.frontBar = IMAGEMANAGER->findImage("volumeFrontBar");
	master.button = IMAGEMANAGER->findImage("volumeButton");
	master.x = 3 * WINSIZEX / 4;
	master.y = WINSIZEY / 2 - 100;
	master.rc = RectMakeCenter(master.x, master.y, master.backBar->getWidth(), master.backBar->getHeight());
	master.width = GAMEMANAGER->getMasterVolume();

	music.backBar = new image;
	music.frontBar = new image;
	music.button = new image;
	music.backBar = IMAGEMANAGER->findImage("volumeBackBar");
	music.frontBar = IMAGEMANAGER->findImage("volumeFrontBar");
	music.button = IMAGEMANAGER->findImage("volumeButton");
	music.x = 3 * WINSIZEX / 4;
	music.y = WINSIZEY / 2;
	music.rc = RectMakeCenter(music.x, music.y, music.backBar->getWidth(), music.backBar->getHeight());
	music.width = GAMEMANAGER->getMusicVolume();

	sfx.backBar = new image;
	sfx.frontBar = new image;
	sfx.button = new image;
	sfx.backBar = IMAGEMANAGER->findImage("volumeBackBar");
	sfx.frontBar = IMAGEMANAGER->findImage("volumeFrontBar");
	sfx.button = IMAGEMANAGER->findImage("volumeButton");
	sfx.x = 3 * WINSIZEX / 4;
	sfx.y = WINSIZEY / 2 + 100;
	sfx.rc = RectMakeCenter(sfx.x, sfx.y, sfx.backBar->getWidth(), sfx.backBar->getHeight());
	sfx.width = GAMEMANAGER->getSfxVolume();
}
