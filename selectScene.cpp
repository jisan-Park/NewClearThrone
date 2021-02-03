#include "stdafx.h"
#include "selectScene.h"

HRESULT selectScene::init()
{
	setImage();
	selectNum = 0;
	selectedImage = new image;
	return S_OK;
}

void selectScene::update()
{
	KEYANIMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown(VK_BACK)) {
		SCENEMANAGER->changeScene("메인메뉴씬");
	}
	for (int i = 0; i < 6; ++i) {
		if (PtInRect(&chr_info[i].info.rc,_ptMouse)) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				selectNum = i+1;
			}
		}
		if (selectNum == i+1) {
			chr_info[i].alpha = 255;
		}
		else {
			chr_info[i].alpha = 100;
		}
	}
	//select character info image
	selectImage();

	//Btn set alpha + Keyupdate
	BtnUpdate();
}

void selectScene::release()
{
}

void selectScene::render()
{
	//background
	IMAGEMANAGER->findImage("background")->aniRender(getMemDC(), 0, 0, KEYANIMANAGER->findAnimation("backgroundAnimation"));

	//character card render
	for (int i = 0; i < 6; ++i) {
		chr_info[i].info.img->alphaRender(getMemDC(),chr_info[i].info.rc.left, chr_info[i].info.rc.top, chr_info[i].alpha);
	}
	if (selectNum !=0) {
		//selected character render
		selectedImage->render(getMemDC(), 0, 160);
	}
	

	//go, back 버튼
	_go.info.img->alphaRender(getMemDC(),_go.info.rc.left, _go.info.rc.top, _go.alpha);
	_back.info.img->alphaRender(getMemDC(), _back.info.rc.left, _back.info.rc.top, _back.alpha);

	//마우스 포인터 render
	RECT _mouse = RectMakeCenter(_ptMouse.x, _ptMouse.y, 40, 40);
	IMAGEMANAGER->findImage("mouse_aim")->render(getMemDC(), _mouse.left, _mouse.top);
}

void selectScene::setImage()
{
	IMAGEMANAGER->addImage("back", "image/Scene/selectScene/back.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("go", "image/Scene/selectScene/go.bmp", 100, 100, true, RGB(255, 0, 255));
	//character Card
	IMAGEMANAGER->addImage("random_character_card","image/Scene/selectScene/random_character_card.bmp",72,108,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("fish_character_card", "image/Scene/selectScene/fish_character_card.bmp", 72, 108, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("crystal_character_card", "image/Scene/selectScene/crystal_character_card.bmp", 72, 108, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("eyes_character_card", "image/Scene/selectScene/eyes_character_card.bmp", 72, 108, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("melting_character_card", "image/Scene/selectScene/melting_character_card.bmp", 72, 108, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("plant_character_card", "image/Scene/selectScene/plant_character_card.bmp", 72, 108, true, RGB(255, 0, 255));
	//selected character info
	IMAGEMANAGER->addImage("random_selected", "image/Scene/selectScene/random_selected.bmp", 1280, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fish_selected", "image/Scene/selectScene/fish_selected.bmp", 1280, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("crystal_selected", "image/Scene/selectScene/crystal_selected.bmp", 1280, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("eyes_selected", "image/Scene/selectScene/eyes_selected.bmp", 1280, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("melting_selected", "image/Scene/selectScene/melting_selected.bmp", 1280, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("plant_selected", "image/Scene/selectScene/plant_selected.bmp", 1280, 400, true, RGB(255, 0, 255));
	
	
	for (int i = 0; i < 6; ++i) {
		chr_info[i].info.img = new image;
	}
	_go.info.img = new image;
	_back.info.img = new image;

	chr_info[0].info.img = IMAGEMANAGER->findImage("random_character_card");
	chr_info[1].info.img = IMAGEMANAGER->findImage("fish_character_card");
	chr_info[2].info.img = IMAGEMANAGER->findImage("crystal_character_card");
	chr_info[3].info.img = IMAGEMANAGER->findImage("eyes_character_card");
	chr_info[4].info.img = IMAGEMANAGER->findImage("melting_character_card");
	chr_info[5].info.img = IMAGEMANAGER->findImage("plant_character_card");

	_go.info.img = IMAGEMANAGER->findImage("go");
	_back.info.img = IMAGEMANAGER->findImage("back");

	for (int i = 0; i < 6; ++i) {
		
		chr_info[i].alpha = 100;
		//center x
		chr_info[i].info.x = (WINSIZEX / 2 - 230) + (92 * i);
		//center y
		chr_info[i].info.y = 104;
		//rect
		chr_info[i].info.rc = RectMakeCenter(
			chr_info[i].info.x,
			chr_info[i].info.y,
			chr_info[i].info.img->getWidth(),
			chr_info[i].info.img->getHeight());
	}
	_go.info.x = 1100;
	_go.info.y = 600;

	_back.info.x = 100;
	_back.info.y = 600;

	_go.info.rc = RectMakeCenter(_go.info.x, _go.info.y, _go.info.img->getWidth(),_go.info.img->getHeight());
	_back.info.rc = RectMakeCenter(_back.info.x, _back.info.y, _back.info.img->getWidth(), _back.info.img->getHeight());

	_go.alpha = 100;
	_back.alpha = 100;
}

void selectScene::selectImage()
{
	switch (selectNum)
	{
	case 1:
		selectedImage = IMAGEMANAGER->findImage("random_selected");
		break;
	case 2:
		selectedImage = IMAGEMANAGER->findImage("fish_selected");
		break;
	case 3:
		selectedImage = IMAGEMANAGER->findImage("crystal_selected");
		break;
	case 4:
		selectedImage = IMAGEMANAGER->findImage("eyes_selected");
		break;
	case 5:
		selectedImage = IMAGEMANAGER->findImage("melting_selected");
		break;
	case 6:
		selectedImage = IMAGEMANAGER->findImage("plant_selected");
		break;
	default:
		break;
	}
}

void selectScene::BtnUpdate()
{
	if (PtInRect(&_go.info.rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SCENEMANAGER->changeScene("게임씬");
		}
		_go.alpha = 255;
	}
	else {
		_go.alpha = 100;
	}
	if (PtInRect(&_back.info.rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SCENEMANAGER->changeScene("메인메뉴씬");
		}
		_back.alpha = 255;
	}
	else {
		_back.alpha = 100;
	}
}
