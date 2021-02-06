#include "stdafx.h"
#include "mainmenuScene.h"

HRESULT mainmenuScene::init()
{
	setImage();
	SOUNDMANAGER->play("메인메뉴", (GAMEMANAGER->getMusicVolume() / 100.0f)*1.0f);

	return S_OK;
}

void mainmenuScene::update()
{
	KEYANIMANAGER->update();

	for (int i = 0; i < 5; i++) {
		if (PtInRect(&selectMenu[i].info.rc, _ptMouse)) {
			selectMenu[i].alpha = 255;
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
				SOUNDMANAGER->play("클릭소리", (GAMEMANAGER->getSfxVolume() / 100.0f)*1.0f);
				switch (i)
				{
				case 0:
					SCENEMANAGER->changeScene("셀렉트씬");
					break;
				case 1:
					if (PLAYERMANAGER->getPlayer() != nullptr) {
						SCENEMANAGER->changeScene("커스텀씬");
					}
					else {
						MessageBox(_hWnd, TEXT("MAPTOOL 에서 PLAYER를 선택해주세요"), TEXT("메시지 박스"), MB_OK);
					}
					break;
				case 2:
					SCENEMANAGER->changeScene("맵툴씬");
					break;
				case 3:
					SCENEMANAGER->changeScene("셋팅씬");
					break;
				case 4:
					//게임종료
					DestroyWindow(_hWnd);
					break;
				default:
					break;
				}
			}
		}
		else {
			selectMenu[i].alpha = 100;
		}
	}
}

void mainmenuScene::release()
{
}

void mainmenuScene::render()
{
	IMAGEMANAGER->findImage("background")->aniRender(getMemDC(), 0, 0, KEYANIMANAGER->findAnimation("backgroundAnimation"));

	for (int i = 0; i < 5; i++) {
		selectMenu[i].info.img->alphaRender(getMemDC(), selectMenu[i].info.rc.left, selectMenu[i].info.rc.top, selectMenu[i].alpha);
	}
	//마우스 포인터 render
	RECT _mouse = RectMakeCenter(_ptMouse.x, _ptMouse.y, 40, 40);
	IMAGEMANAGER->findImage("mouse_aim")->render(getMemDC(), _mouse.left, _mouse.top);
}

void mainmenuScene::setImage()
{
	IMAGEMANAGER->addImage("gameplay", "image/scene/mainmenu/gameplay.bmp", 237, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("customplay", "image/scene/mainmenu/customplay.bmp", 295, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("maptool", "image/scene/mainmenu/maptool.bmp", 209, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("settingBtn", "image/scene/mainmenu/setting.bmp", 184, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("quit", "image/scene/mainmenu/quit.bmp", 99, 38, true, RGB(255, 0, 255));

	selectMenu[0].info.img = IMAGEMANAGER->findImage("gameplay");
	selectMenu[0].info.x = WINSIZEX / 2;
	selectMenu[0].info.y = WINSIZEY / 2 - selectMenu[0].info.img->getHeight() / 2 - 200;
	selectMenu[0].alpha = 100;

	selectMenu[1].info.img = IMAGEMANAGER->findImage("customplay");
	selectMenu[1].info.x = WINSIZEX / 2;
	selectMenu[1].info.y = WINSIZEY / 2 - selectMenu[1].info.img->getHeight() / 2 - 100;
	selectMenu[1].alpha = 100;

	selectMenu[2].info.img = IMAGEMANAGER->findImage("maptool");
	selectMenu[2].info.x = WINSIZEX / 2;
	selectMenu[2].info.y = WINSIZEY / 2 - selectMenu[2].info.img->getHeight() / 2;
	selectMenu[2].alpha = 100;

	selectMenu[3].info.img = IMAGEMANAGER->findImage("settingBtn");
	selectMenu[3].info.x = WINSIZEX / 2;
	selectMenu[3].info.y = WINSIZEY / 2 - selectMenu[3].info.img->getHeight() / 2 + 100;
	selectMenu[3].alpha = 100;

	selectMenu[4].info.img = IMAGEMANAGER->findImage("quit");
	selectMenu[4].info.x = WINSIZEX / 2;
	selectMenu[4].info.y = WINSIZEY / 2 - selectMenu[4].info.img->getHeight() / 2 + 200;
	selectMenu[4].alpha = 100;

	for (int i = 0; i < 5; ++i) {
		selectMenu[i].info.rc = RectMakeCenter(
			selectMenu[i].info.x,
			selectMenu[i].info.y,
			selectMenu[i].info.img->getWidth(),
			selectMenu[i].info.img->getHeight()
		);
	}
}