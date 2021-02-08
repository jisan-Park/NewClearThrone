#include "stdafx.h"
#include "gameManager.h"
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
HRESULT gameManager::init()
{
	master_volume = 1.0f;
	music_volume = 0.5f;
	sfx_volume = 0.5f;

	IMAGEMANAGER->addImage("black", "image/Scene/black.bmp", 1280, 720, true, RGB(255, 0, 255));
	setVolumeImage();
	setPauseImage();
	//setUIImage();

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

void gameManager::setUIImage()
{
	//stage
	IMAGEMANAGER->addImage("stage", "image/ui/stage.bmp", 66, 14, true, RGB(255, 0, 255));
	//number
	IMAGEMANAGER->addFrameImage("number","image/ui/number.bmp",140,15,10,1,true,RGB(255,0,255));
	//hp
	IMAGEMANAGER->addImage("hp_slash","image/ui/hp/slash.bmp",11,15,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("hpbar_back", "image/ui/hp/hpbar_back.bmp", 250, 35, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hpbar_front", "image/ui/hp/hpbar_front.bmp", 250, 35, true, RGB(255, 0, 255));
	//bulletCount
	IMAGEMANAGER->addImage("bullet_back", "image/ui/bulletCount/bullet_back.bmp", 21, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bullet_front", "image/ui/bulletCount/bullet_front.bmp", 21, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shell_back", "image/ui/bulletCount/shell_back.bmp", 16, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shell_front", "image/ui/bulletCount/shell_front.bmp", 16, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("energy_back", "image/ui/bulletCount/energy_back.bmp", 18, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("energy_front", "image/ui/bulletCount/energy_front.bmp", 18, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("explosive_back", "image/ui/bulletCount/explosive_back.bmp", 21, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("explosive_front", "image/ui/bulletCount/explosive_front.bmp", 21, 26, true, RGB(255, 0, 255));
	//weaponIcon
	IMAGEMANAGER->addImage("assultrifle_icon", "image/ui/weaponIcon/assultrifle_icon.bmp", 50, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("grenadelauncher_icon", "image/ui/weaponIcon/grenadelauncher_icon.bmp", 57, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("machinegun_icon", "image/ui/weaponIcon/machinegun_icon.bmp", 67, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pistol_icon", "image/ui/weaponIcon/pistol_icon.bmp", 36, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("razerrifle_icon", "image/ui/weaponIcon/razerrifle_icon.bmp", 57, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shotgun_icon", "image/ui/weaponIcon/shotgun_icon.bmp", 47, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shovel_icon", "image/ui/weaponIcon/shovel_icon.bmp", 58, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sword_icon", "image/ui/weaponIcon/sword_icon.bmp", 46, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("triplemachinegun_icon", "image/ui/weaponIcon/triplemachinegun_icon.bmp", 49, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wrench_icon", "image/ui/weaponIcon/wrench_icon.bmp", 33, 11, true, RGB(255, 0, 255));

	stage.img = new image;
	stage.img = IMAGEMANAGER->findImage("stage");
	stage.x = 0;
	stage.y = 0;
	
	round[0].img = new image;
	round[1].img = new image;
	round_slash.img = new image;

	round[0].img = IMAGEMANAGER->findImage("number");
	round[1].img = IMAGEMANAGER->findImage("number");
	round_slash.img = IMAGEMANAGER->findImage("hp_slash");

	round[0].x = 64 + 10;
	round[1].x = 64 + 40;
	round_slash.x = 64 + 25;

	round[0].currentFrameX = MAPMANAGER->getStage_first() + 1;
	round[1].currentFrameX = MAPMANAGER->getStage_second() + 1;
	round[0].currentFrameY = 0;
	round[1].currentFrameY = 0;
	
	round[0].y = round[1].y = round_slash.y = 0;


	//new image
	//체력바
	HP.backBar = new image;
	HP.frontBar = new image;
	hpSlash.img = new image;

	HP.backBar = IMAGEMANAGER->findImage("hpbar_back");
	HP.frontBar = IMAGEMANAGER->findImage("hpbar_front");
	HP.x = 0;
	HP.y = 20;
	HP.width = (int)(((float)PLAYERMANAGER->getPlayer()->getHp() / (float)PLAYERMANAGER->getPlayer()->getMaxhp()) * (float)HP.backBar->getWidth());
	hpSlash.img = IMAGEMANAGER->findImage("hp_slash");
	hpSlash.x = HP.backBar->getWidth() / 2;
	hpSlash.y = HP.y+10;

	//체력 숫자
	for (int i = 0; i < 2; ++i) {
		currentHP[i].img = new image;
		maxHP[i].img = new image;

		currentHP[i].img = IMAGEMANAGER->findImage("number");
		maxHP[i].img = IMAGEMANAGER->findImage("number");

		currentHP[1 - i].x = HP.backBar->getWidth() / 2 - 24 - (19 * i);
		maxHP[i].x = HP.backBar->getWidth() / 2 + 24 + (19 * i);

		currentHP[i].y = HP.y + 10;
		maxHP[i].y = HP.y + 10;

		currentHP[i].currentFrameY = 0;
		maxHP[i].currentFrameY = 0;
	}

	maxHP[0].currentFrameX = PLAYERMANAGER->getPlayer()->getMaxhp() / 10;
	maxHP[1].currentFrameX = PLAYERMANAGER->getPlayer()->getMaxhp() % 10;

	currentHP[0].currentFrameX = PLAYERMANAGER->getPlayer()->getHp() / 10;
	currentHP[1].currentFrameX = PLAYERMANAGER->getPlayer()->getHp() % 10;
	
	//현재, 서브 무기이미지 + 총알 개수
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 3; ++j) {
			bulletCountNumber[i][j].img = new image;
			bulletCountNumber[i][j].img = IMAGEMANAGER->findImage("number");
			bulletCountNumber[i][j].x = 50 + (j * 20);
			bulletCountNumber[i][j].y = 70 + (i * 30);
			bulletCountNumber[i][j].currentFrameY = 0;
			
		}
	}
	bulletCountNumber[0][0].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerbullet() / 100;
	bulletCountNumber[0][1].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerbullet() % 100 / 10;
	bulletCountNumber[0][2].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerbullet() % 10;

	bulletCountNumber[1][0].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayershellb() / 100;
	bulletCountNumber[1][1].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayershellb() % 100 / 10;
	bulletCountNumber[1][2].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayershellb() % 10;

	bulletCountNumber[2][0].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerenergyb() / 100;
	bulletCountNumber[2][1].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerenergyb() % 100 / 10;
	bulletCountNumber[2][2].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerenergyb() % 10;

	bulletCountNumber[3][0].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerexplodeb() / 100;
	bulletCountNumber[3][1].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerexplodeb() % 100 / 10;
	bulletCountNumber[3][2].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerexplodeb() % 10;
	
	//bulletCount set
	for (int i = 0; i < 4; ++i) {
		bulletCount[i].backBar = new image;
		bulletCount[i].frontBar = new image;
		bulletCount[i].x = 25;
		bulletCount[i].y = 70 + (i * 30);
	}
	bulletCount[0].backBar = IMAGEMANAGER->findImage("bullet_back");
	bulletCount[0].frontBar = IMAGEMANAGER->findImage("bullet_front");
	bulletCount[1].backBar = IMAGEMANAGER->findImage("shell_back");
	bulletCount[1].frontBar = IMAGEMANAGER->findImage("shell_front");
	bulletCount[2].backBar = IMAGEMANAGER->findImage("energy_back");
	bulletCount[2].frontBar = IMAGEMANAGER->findImage("energy_front");
	bulletCount[3].backBar = IMAGEMANAGER->findImage("explosive_back");
	bulletCount[3].frontBar = IMAGEMANAGER->findImage("explosive_front");

	bulletCount[0].width = (int)(((float)PLAYERMANAGER->getPlayer()->getPlayerbullet() / (float)PLAYERMANAGER->getPlayer()->getPlayerMaxBullet()) * (float)bulletCount[0].backBar->getWidth());
	bulletCount[1].width = (int)(((float)PLAYERMANAGER->getPlayer()->getPlayershellb() / (float)PLAYERMANAGER->getPlayer()->getPlayerMaxShell()) * (float)bulletCount[1].backBar->getWidth());
	bulletCount[2].width = (int)(((float)PLAYERMANAGER->getPlayer()->getPlayerenergyb() / (float)PLAYERMANAGER->getPlayer()->getPlayerMaxEnergy()) * (float)bulletCount[2].backBar->getWidth());
	bulletCount[3].width = (int)(((float)PLAYERMANAGER->getPlayer()->getPlayerexplodeb() / (float)PLAYERMANAGER->getPlayer()->getPlayerMaxExplosive()) * (float)bulletCount[3].backBar->getWidth());
}

void gameManager::updateUI()
{
	//라운드 숫자 변화
	round[0].currentFrameX = MAPMANAGER->getStage_first() + 1;
	round[1].currentFrameX = MAPMANAGER->getStage_second() + 1;

	//bullet count 변화
	bulletCountNumber[0][0].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerbullet() / 100;
	bulletCountNumber[0][1].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerbullet() % 100 / 10;
	bulletCountNumber[0][2].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerbullet() % 10;

	bulletCountNumber[1][0].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayershellb() / 100;
	bulletCountNumber[1][1].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayershellb() % 100 / 10;
	bulletCountNumber[1][2].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayershellb() % 10;

	bulletCountNumber[2][0].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerenergyb() / 100;
	bulletCountNumber[2][1].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerenergyb() % 100 / 10;
	bulletCountNumber[2][2].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerenergyb() % 10;

	bulletCountNumber[3][0].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerexplodeb() / 100;
	bulletCountNumber[3][1].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerexplodeb() % 100 / 10;
	bulletCountNumber[3][2].currentFrameX = PLAYERMANAGER->getPlayer()->getPlayerexplodeb() % 10;

	//bullet count 변화에 따른 이미지 render width 변경
	bulletCount[0].width = (int)(((float)PLAYERMANAGER->getPlayer()->getPlayerbullet() / (float)PLAYERMANAGER->getPlayer()->getPlayerMaxBullet()) * (float)bulletCount[0].backBar->getWidth());
	bulletCount[1].width = (int)(((float)PLAYERMANAGER->getPlayer()->getPlayershellb() / (float)PLAYERMANAGER->getPlayer()->getPlayerMaxShell()) * (float)bulletCount[1].backBar->getWidth());
	bulletCount[2].width = (int)(((float)PLAYERMANAGER->getPlayer()->getPlayerenergyb() / (float)PLAYERMANAGER->getPlayer()->getPlayerMaxEnergy()) * (float)bulletCount[2].backBar->getWidth());
	bulletCount[3].width = (int)(((float)PLAYERMANAGER->getPlayer()->getPlayerexplodeb() / (float)PLAYERMANAGER->getPlayer()->getPlayerMaxExplosive()) * (float)bulletCount[3].backBar->getWidth());
	//hp변화에 따른 숫자 변경
	maxHP[0].currentFrameX = PLAYERMANAGER->getPlayer()->getMaxhp() / 10;
	maxHP[1].currentFrameX = PLAYERMANAGER->getPlayer()->getMaxhp() % 10;
	currentHP[0].currentFrameX = PLAYERMANAGER->getPlayer()->getHp() / 10;
	currentHP[1].currentFrameX = PLAYERMANAGER->getPlayer()->getHp() % 10;
	//hp변화에 따른 색 width 변경
	HP.width = (int)(((float)PLAYERMANAGER->getPlayer()->getHp() / (float)PLAYERMANAGER->getPlayer()->getMaxhp()) * (float)HP.backBar->getWidth());
}

void gameManager::UIRender(HDC hdc)
{
	stage.img->render(hdc,stage.x,stage.y);
	round[0].img->frameRender(hdc, round[0].x, round[0].y, round[0].currentFrameX, round[0].currentFrameY);
	round[1].img->frameRender(hdc, round[1].x, round[1].y, round[1].currentFrameX, round[1].currentFrameY);
	round_slash.img->render(hdc,round_slash.x, round_slash.y);

	//체력바
	HP.frontBar->render(hdc, HP.x, HP.y, 0, 0, HP.width, HP.backBar->getHeight());
	HP.backBar->render(hdc, HP.x, HP.y);
	hpSlash.img->render(hdc,hpSlash.x, hpSlash.y);

	//체력 숫자
	for (int i = 0; i < 2; ++i) {
		currentHP[i].img->frameRender(hdc,currentHP[i].x, currentHP[i].y, currentHP[i].currentFrameX, currentHP[i].currentFrameY);
		maxHP[i].img->frameRender(hdc, maxHP[i].x, maxHP[i].y, maxHP[i].currentFrameX, maxHP[i].currentFrameY);
	}
	////bullet render
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 3; ++j) {
			bulletCountNumber[i][j].img->frameRender(
				hdc,
				bulletCountNumber[i][j].x,
				bulletCountNumber[i][j].y,
				bulletCountNumber[i][j].currentFrameX,
				bulletCountNumber[i][j].currentFrameY);
		}
	}

	//총알 이미지로 보여주기 //0:bullet, 1:shell, 2:energy, 3:explosive
	for (int i = 0; i < 4; ++i) {
		bulletCount[i].backBar->render(hdc, bulletCount[i].x, bulletCount[i].y);
		bulletCount[i].frontBar->render(hdc, bulletCount[i].x, bulletCount[i].y,0,0, bulletCount[i].width, bulletCount[i].backBar->getHeight());
	}
}

void gameManager::getWeaponIcon(image* img, weaponType t)
{
	switch (t)
	{
	case ASSULTRIFLE:
		img = IMAGEMANAGER->findImage("assultrifle_icon");
		break;
	case GRENADELAUNCHER:
		img = IMAGEMANAGER->findImage("grenadelauncher_icon");
		break;
	case MACHINEGUN:
		img = IMAGEMANAGER->findImage("machinegun_icon");
		break;
	case PISTOL:
		img = IMAGEMANAGER->findImage("pistol_icon");
		break;
	case RAZERRIFLE:
		img = IMAGEMANAGER->findImage("razerrifle_icon");
		break;
	case SHOTGUN:
		img = IMAGEMANAGER->findImage("shotgun_icon");
		break;
	case SHOVEL:
		img = IMAGEMANAGER->findImage("shovel_icon");
		break;
	case SWORD:
		img = IMAGEMANAGER->findImage("sword_icon");
		break;
	case TRIPLEMACHINEGUN:
		img = IMAGEMANAGER->findImage("triplemachinegun_icon");
		break;
	case WRENCH:
		img = IMAGEMANAGER->findImage("wrench_icon");
		break;
	default:
		break;
	}
}

void gameManager::volumeCheck()
{
	//마우스 설정에 따른 볼륨조절
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&master.rc, _ptMouse))
		{
			master_volume = ((float)(_ptMouse.x - master.rc.left) / (float)(master.rc.right - master.rc.left));
		}
		if (PtInRect(&music.rc, _ptMouse))
		{
			music_volume = ((float)(_ptMouse.x - music.rc.left) / (float)(music.rc.right - music.rc.left));
		}
		if (PtInRect(&sfx.rc, _ptMouse))
		{
			sfx_volume = ((float)(_ptMouse.x - sfx.rc.left) / (float)(sfx.rc.right - sfx.rc.left));
		}
	}
	//volume 조절에 따른 render 변화를 위한 변수들 set
	master.width = (int)((master_volume / 1.0f) * master.backBar->getWidth());
	master.center.x = master.rc.left + master.width;

	music.width = (int)((music_volume / 1.0f) * music.backBar->getWidth());
	music.center.x = music.rc.left + music.width;

	sfx.width = (int)((sfx_volume / 1.0f) * sfx.backBar->getWidth());
	sfx.center.x = sfx.rc.left + sfx.width;
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
	master.width = (int)((master_volume/1.0f) * master.backBar->getWidth());
	master.center.x = master.rc.left + master.width;
	master.center.y = master.rc.top;

	music.backBar = new image;
	music.frontBar = new image;
	music.button = new image;
	music.backBar = IMAGEMANAGER->findImage("volumeBackBar");
	music.frontBar = IMAGEMANAGER->findImage("volumeFrontBar");
	music.button = IMAGEMANAGER->findImage("volumeButton");
	music.x = 3 * WINSIZEX / 4;
	music.y = WINSIZEY / 2;
	music.rc = RectMakeCenter(music.x, music.y, music.backBar->getWidth(), music.backBar->getHeight());
	music.width = (int)((music_volume / 1.0f) * music.backBar->getWidth());
	music.center.x = music.rc.left + music.width;
	music.center.y = music.rc.top;

	sfx.backBar = new image;
	sfx.frontBar = new image;
	sfx.button = new image;
	sfx.backBar = IMAGEMANAGER->findImage("volumeBackBar");
	sfx.frontBar = IMAGEMANAGER->findImage("volumeFrontBar");
	sfx.button = IMAGEMANAGER->findImage("volumeButton");
	sfx.x = 3 * WINSIZEX / 4;
	sfx.y = WINSIZEY / 2 + 100;
	sfx.rc = RectMakeCenter(sfx.x, sfx.y, sfx.backBar->getWidth(), sfx.backBar->getHeight());
	sfx.width = (int)((sfx_volume / 1.0f) * sfx.backBar->getWidth());
	sfx.center.x = sfx.rc.left + sfx.width;
	sfx.center.y = sfx.rc.top;

}

void gameManager::volumeUpdate()
{
	volumeCheck();

	if (PtInRect(&back.info.rc, _ptMouse)) {
		back.alpha = 255;
		
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			if (isPaused && isSetting) {
				isSetting = false;
			}
			else {
				SCENEMANAGER->changeScene("메인메뉴씬");
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
	master.frontBar->render(hdc, master.rc.left, master.rc.top, 0, 0, master.width, master.backBar->getHeight());
	music.frontBar->render(hdc, music.rc.left, music.rc.top, 0, 0, music.width, music.backBar->getHeight());
	sfx.frontBar->render(hdc, sfx.rc.left, sfx.rc.top, 0, 0, sfx.width, sfx.backBar->getHeight());

	//volume back Bar
	master.backBar->render(hdc, master.rc.left, master.rc.top);
	music.backBar->render(hdc, music.rc.left, music.rc.top);
	sfx.backBar->render(hdc, sfx.rc.left, sfx.rc.top);

	//volume button
	master.button->render(hdc, master.center.x, master.center.y);
	music.button->render(hdc, music.center.x, music.center.y);
	sfx.button->render(hdc, sfx.center.x, sfx.center.y);

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
					SCENEMANAGER->changeScene("메인메뉴씬");
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
