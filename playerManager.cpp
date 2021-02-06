#include "stdafx.h"
#include "playerManager.h"

playerManager::playerManager()
{
}

playerManager::~playerManager()
{
}

HRESULT playerManager::init()
{
	/*
	setplayer(
		(PLAYERTYPE)MAPMANAGER->getPlayerType(),
		MAPMANAGER->getPlayerPoint().x,
		MAPMANAGER->getPlayerPoint().y);*/

	return S_OK;
}

void playerManager::release()
{
}

void playerManager::update()
{
	_player->update();
}

void playerManager::render(HDC hdc)
{
	_player->render(hdc);
}

void playerManager::setplayer(PLAYERTYPE playerType, int x, int y)
{
	int temp;
	_playertype = playerType;

	switch (_playertype)
	{
	case FISH:
		_player = new Fish;
		break;
	case CRYSTAL:
		_player = new Crystal;
		break;
	case EYES:
		_player = new Eyes;
		break;
	case MELTING:
		_player = new Meiting;
		break;
	case PLANT:
		_player = new Plant;
		break;
	case RANDOM:
		temp = RND->getInt(5);
		setplayer((PLAYERTYPE)temp,x,y);
		break;
	default:
		break;
	}
	_player->init(x,y);
}

void playerManager::setimage()
{
	IMAGEMANAGER->addFrameImage("fish_idle", "image/player/fish/fish_idle.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fish_walk", "image/player/fish/fish_walk.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fish_hit", "image/player/fish/fish_hit.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fish_dead", "image/player/fish/fish_dead.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("crystal_idle", "image/player/crystal/crystal_idle.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("crystal_walk", "image/player/crystal/crystal_walk.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("crystal_hit", "image/player/crystal/crystal_hit.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("crystal_dead", "image/player/crystal/crystal_dead.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("crystal_skill", "image/player/crystal/crystal_skill.bmp", 360, 68, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("eyes_idle", "image/player/eyes/eyes_idle.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eyes_walk", "image/player/eyes/eyes_walk.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eyes_hit", "image/player/eyes/eyes_hit.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eyes_dead", "image/player/eyes/eyes_dead.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eyes_skill", "image/player/eyes/eyes_skill.bmp", 216, 28, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("melting_idle", "image/player/melting/melting_idle.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("melting_walk", "image/player/melting/melting_walk.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("melting_hit", "image/player/melting/melting_hit.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("melting_dead", "image/player/melting/melting_dead.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("melting_menuidle", "image/player/melting/melting_menuidle.bmp", 816, 48, 17, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("plant_idle", "image/player/plant/plant_idle.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("plant_walk", "image/player/plant/plant_walk.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("plant_hit", "image/player/plant/plant_hit.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("plant_dead", "image/player/plant/plant_dead.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("plant_skill", "image/player/plant/plant_skill.bmp", 360, 74, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("plant_menuidle", "image/player/plant/plant_menuidle.bmp", 704, 128, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("plant_bullet", "image/bullet/plant_bullet.bmp", 21, 21, true, RGB(255, 0, 255));
}
