#include "stdafx.h"
#include "weaponManager.h"

void weaponManager::init()
{
	setImage();
	//test = new razerRifle;
	//test->init(PointMake(WINSIZEX / 2, WINSIZEY / 2));

}

void weaponManager::release()
{
}

void weaponManager::update()
{
	//test->setAngle(getAngle(WINSIZEX / 2, WINSIZEY / 2, _ptMouse.x, _ptMouse.y));
	//test->update();
}

void weaponManager::render(HDC hdc)
{
	//test->render(hdc);
}

void weaponManager::setImage()
{
	IMAGEMANAGER->addFrameImage("assultrifle", "image/weapon/assultrifle.bmp", 640, 40, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grenadelauncher", "image/weapon/grenadelauncher.bmp", 704, 44, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("machinegun", "image/weapon/machinegun.bmp", 768, 48, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pistol", "image/weapon/pistol.bmp", 288, 18, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("razerrifle", "image/weapon/razerrifle.bmp", 768, 48, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shotgun", "image/weapon/shotgun.bmp", 672, 42, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovel", "image/weapon/shovel.bmp", 1024, 64, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shoveldrop", "image/weapon/shoveldrop.bmp", 448, 18, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword", "image/weapon/sword.bmp", 960, 60, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sworddrop", "image/weapon/sworddrop.bmp", 420, 10, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("triplemachinegun", "image/weapon/triplemachinegun.bmp", 784, 49, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wrench", "image/weapon/wrench.bmp", 720, 45, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wrenchdrop", "image/weapon/wrenchdrop.bmp", 380, 14, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bullet16", "image/bullet/bullet16.bmp", 512, 32, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bullet1", "image/bullet/bullet1.bmp", 24, 24, true, RGB(255, 0, 255));
}
