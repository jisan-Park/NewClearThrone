#include "stdafx.h"
#include "settingScene.h"

HRESULT settingScene::init()
{
	setImage();
	return S_OK;
}

void settingScene::update()
{
	GAMEMANAGER->volumeUpdate();
	KEYANIMANAGER->update();
}

void settingScene::release()
{
}

void settingScene::render()
{
	IMAGEMANAGER->findImage("background")->aniRender(getMemDC(), 0, 0, KEYANIMANAGER->findAnimation("backgroundAnimation"));
	GAMEMANAGER->volumeRender(getMemDC());
	//마우스 포인터 render
	RECT _mouse = RectMakeCenter(_ptMouse.x, _ptMouse.y, 40, 40);
	IMAGEMANAGER->findImage("mouse_aim")->render(getMemDC(), _mouse.left, _mouse.top);
}

void settingScene::setImage()
{
	
}
