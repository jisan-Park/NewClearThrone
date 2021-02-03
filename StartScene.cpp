#include "stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init()
{
	setImage();

	_logo.info.img = IMAGEMANAGER->findImage("logo");
	_logo.info.x = WINSIZEX / 2 - 300;
	_logo.info.y = 0;
	_logo.alpha = 0;

	_pressEnter.info.img = IMAGEMANAGER->findImage("pressEnter");
	_pressEnter.info.x = WINSIZEX / 2 - 154;
	_pressEnter.info.y = WINSIZEY - 100;
	_pressEnter.alpha = 0;

	interval = 0;

	return S_OK;
}

void StartScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		SCENEMANAGER->changeScene("메인메뉴씬");
	}
	interval += TIMEMANAGER->getElapsedTime();

	if (_logo.alpha < 255) {
		_logo.alpha++;
	}
	if (_logo.info.y < WINSIZEY / 2 - 103) {
		_logo.info.y++;
	}
	//logo가 정위치에 도착했으면
	else {
		//interval by ElapsedTime
		if (interval >= 0.5) {
			interval = 0;

			if (_pressEnter.alpha == 0) {
				_pressEnter.alpha = 255;
			}
			else {
				_pressEnter.alpha = 0;
			}
		}

	}

	KEYANIMANAGER->update();
}

void StartScene::release()
{
}

void StartScene::render()
{
	IMAGEMANAGER->findImage("background")->aniRender(getMemDC(), 0, 0, KEYANIMANAGER->findAnimation("backgroundAnimation"));

	_logo.info.img->alphaRender(getMemDC(), _logo.info.x, _logo.info.y, _logo.alpha);
	_pressEnter.info.img->alphaRender(getMemDC(), _pressEnter.info.x, _pressEnter.info.y, _pressEnter.alpha);
}

void StartScene::setImage()
{
	IMAGEMANAGER->addFrameImage("background", "image/scene/background.bmp", 25600, 720, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("logo", "image/scene/startScene/logo.bmp", 600, 206, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pressEnter", "image/scene/startScene/pressEnter.bmp", 308, 18, true, RGB(255, 0, 255));

	KEYANIMANAGER->addCoordinateFrameAnimation("backgroundAnimation", "background", 0, 19, 10, false, true);
	KEYANIMANAGER->start("backgroundAnimation");
}
