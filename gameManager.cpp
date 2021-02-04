#include "stdafx.h"
#include "gameManager.h"

HRESULT gameManager::init()
{
	IMAGEMANAGER->addImage("black", "image/Scene/black.bmp", 1280, 720, true, RGB(255, 0, 255));
	setVolumeImage();
	setPauseImage();
	master_volume = 100.0f;
	music_volume = 50.0f;
	sfx_volume = 50.0f;

	isPaused = false;
	isSetting = false;

	return S_OK;
}

void gameManager::update()
{
}

void gameManager::release()
{
}

void gameManager::render(HDC hdc)
{
}

void gameManager::setVolumeImage()
{
	IMAGEMANAGER->addImage("back", "image/scene/back.bmp", 74, 25, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("master_volume", "image/gamemanager/master_volume.bmp", 238, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("music_volume", "image/gamemanager/music_volume.bmp", 213, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sfx_volume", "image/gamemanager/sfx_volume.bmp", 183, 25, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("volumeBackBar", "image/gamemanager/volumeBackBar.bmp", 300, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("volumeFrontBar", "image/gamemanager/volumeFrontBar.bmp", 300, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("volumeButton", "image/gamemanager/volumeButton.bmp", 10, 50, true, RGB(255, 0, 255));

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

void gameManager::volumeUpdate()
{
	if (PtInRect(&back.info.rc, _ptMouse)) {
		back.alpha = 255;
		
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			if (isPaused && isSetting) {
				isSetting = false;
			}
			else {
				SCENEMANAGER->changeScene("¸ÞÀÎ¸Þ´º¾À");
			}
		}
	}
	else {
		back.alpha = 100;
	}
}

void gameManager::volumeRender(HDC hdc)
{
	IMAGEMANAGER->findImage("black")->alphaRender(hdc, 150);
	//volume name
	IMAGEMANAGER->findImage("master_volume")->render(hdc, WINSIZEX / 8, WINSIZEY / 2 - 100);
	IMAGEMANAGER->findImage("music_volume")->render(hdc, WINSIZEX / 8, WINSIZEY / 2);
	IMAGEMANAGER->findImage("sfx_volume")->render(hdc, WINSIZEX / 8, WINSIZEY / 2 + 100);

	//volume front Bar
	master.frontBar->render(hdc, master.rc.left, master.rc.top, 0, 0, ((master.width / 100.0f) * master.backBar->getWidth()), master.backBar->getHeight());
	music.frontBar->render(hdc, music.rc.left, music.rc.top, 0, 0, ((music.width / 100.0f) * music.backBar->getWidth()), music.backBar->getHeight());
	sfx.frontBar->render(hdc, sfx.rc.left, sfx.rc.top, 0, 0, ((sfx.width / 100.0f) * sfx.backBar->getWidth()), sfx.backBar->getHeight());

	//volume back Bar
	master.backBar->render(hdc, master.rc.left, master.rc.top);
	music.backBar->render(hdc, music.rc.left, music.rc.top);
	sfx.backBar->render(hdc, sfx.rc.left, sfx.rc.top);

	//volume button
	master.button->render(hdc, master.rc.left + ((master.width / 100.0f) * master.backBar->getWidth()), master.rc.top);
	music.button->render(hdc, music.rc.left + ((music.width / 100.0f) * music.backBar->getWidth()), music.rc.top);
	sfx.button->render(hdc, sfx.rc.left + ((sfx.width / 100.0f) * sfx.backBar->getWidth()), sfx.rc.top);

	//back button
	back.info.img->alphaRender(hdc, back.info.rc.left, back.info.rc.top, back.alpha);
}

void gameManager::setPauseImage()
{
	IMAGEMANAGER->addImage("mainmenu", "image/gamemanager/mainmenu.bmp", 365, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("setting", "image/gamemanager/setting.bmp", 285, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("retry", "image/gamemanager/retry.bmp", 207, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("continue", "image/gamemanager/continue.bmp", 338, 36, true, RGB(255, 0, 255));
	
	for (int i = 0; i < 4; ++i) {
		pausedBtn[i].alpha = 100;
		pausedBtn[i].info.img = new image;
	}
	pausedBtn[0].info.img = IMAGEMANAGER->findImage("mainmenu");
	pausedBtn[1].info.img = IMAGEMANAGER->findImage("setting");
	pausedBtn[2].info.img = IMAGEMANAGER->findImage("retry");
	pausedBtn[3].info.img = IMAGEMANAGER->findImage("continue");

	pausedBtn[0].info.x = 50 + pausedBtn[0].info.img->getWidth() / 2;
	pausedBtn[1].info.x = 50 + pausedBtn[1].info.img->getWidth() / 2;
	pausedBtn[2].info.x = WINSIZEX - 50 - pausedBtn[2].info.img->getWidth() / 2;
	pausedBtn[3].info.x = WINSIZEX - 50 - pausedBtn[3].info.img->getWidth() / 2;

	pausedBtn[0].info.y = WINSIZEY - 400;
	pausedBtn[1].info.y = WINSIZEY - 200;
	pausedBtn[2].info.y = WINSIZEY - 400;
	pausedBtn[3].info.y = WINSIZEY - 200;

	for (int i = 0; i < 4; ++i) {
		pausedBtn[i].info.rc = RectMakeCenter(pausedBtn[i].info.x, pausedBtn[i].info.y, pausedBtn[i].info.img->getWidth(), pausedBtn[i].info.img->getHeight());
	}
}

void gameManager::pauseUpdate()
{
	for (int i = 0; i < 4; ++i) {
		if (PtInRect(&pausedBtn[i].info.rc, _ptMouse)) 
		{
			pausedBtn[i].alpha = 255;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				if (i == 0) {
					SCENEMANAGER->changeScene("¸ÞÀÎ¸Þ´º¾À");
				}
				else if (i == 1) {
					isSetting = true;
				}
				else if (i == 2) {
					//retry
				}
				else if (i == 3) {
					//continue
					isPaused = false;
				}
			}
		}
		else {
			pausedBtn[i].alpha = 100;
		}
	}
}

void gameManager::pauseRender(HDC hdc)
{
	if (isPaused) {
		IMAGEMANAGER->findImage("black")->alphaRender(hdc,150);

		for (int i = 0; i < 4; ++i) {
			pausedBtn[i].info.img->alphaRender(
				hdc,
				pausedBtn[i].info.rc.left,
				pausedBtn[i].info.rc.top,
				pausedBtn[i].alpha);
		}
		if (isSetting) {
			volumeRender(hdc);
		}
	}
}
