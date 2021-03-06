#include "stdafx.h"
#include "mapManager.h"
//
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
//
HRESULT mapManager::init()
{
	//setter
	setImage();
	setTiles();
	setSampleTile();
	setTileRect();
	
	//left, top tile index
	//가로, 세로 개수
	_pt.x = _pt.y = 0;
	width_count = height_count = 0;
	//크기
	size = 0;

	//랜덤맵 초기화
	_rnd = 3;

	//player set
	player_pt.x = 0, player_pt.y = 0;
	player_type = 0;
	////////////////////[ stage ]///////////////////////////
	stage_first = 0;
	stage_second = 0;

	enemyCount = 10;
	bulletBoxCount = 5;
	weaponBoxCount = 2;
	medikitBoxCount = 2;

	IMAGEMANAGER->addFrameImage("portal","image/effect/portal.bmp",312,78,4,1,true,RGB(255,0,255));

	portal.img = new image;
	portal.img = IMAGEMANAGER->findImage("portal");
	portal_animation = new animation;
	portal_animation->init("portal");
	portal_animation->setPlayFrame(0,3,false,true);
	portal_animation->setFPS(10);

	return S_OK;
}

void mapManager::update()
{
}

void mapManager::release()
{
}

bool mapManager::isCollisionTile(POINT& pt, int width, int height)
{
	RECT playerRect = RectMakeCenter(pt.x,pt.y, width, height);
	RECT temp;
	for (int i = 0; i < TILEX; ++i) {
		for (int j = 0; j < TILEY; ++j) {
			POINT _tileCenter = PointMake(
				_tiles[i][j].rc.left + (_tiles[i][j].rc.right - _tiles[i][j].rc.left),
				_tiles[i][j].rc.top + (_tiles[i][j].rc.bottom - _tiles[i][j].rc.top));

			if (_tiles[i][j].wall == WALL_NONE) {
				continue;
			}
			////벽이 있는 타일과의 거리가 한타일 이상 차이 나면
			//if ( 32 > getDistance(pt, _tileCenter)) {
			//	//왼쪽에서 부딫쳤다면
			//	if (pt.x < _tileCenter.x) {
			//		pt.x = _tileCenter.x - 32;
			//		if (pt.y < _tileCenter.x) {
			//			pt.y = _tileCenter.y - 32;
			//		}
			//		else {
			//			pt.y = _tileCenter.y + 32;
			//		}
			//	}
			//	else {
			//		pt.x = _tileCenter.x + 32;
			//		if (pt.y < _tileCenter.x) {
			//			pt.y = _tileCenter.y - 32;
			//		}
			//		else {
			//			pt.y = _tileCenter.y + 32;
			//		}
			//	}
			//	
			//	
			//	return true;
			//}
			//벽이 있는 타일과 충돌하면
			if (IntersectRect(&temp, &playerRect, &_tiles[i][j].rc)) {
				//가로가 넓다 = 위, 아래에서 충돌했다
				if (temp.right - temp.left > temp.bottom - temp.top) {
					//top이 같다 = 아래에서 충돌했다
					if (playerRect.top == temp.top) {
						//밑으로 밀어줘야함 +
						pt.y += temp.bottom - temp.top;
					}
					else {
						//위로 밀어줘야함 -
						pt.y -= temp.bottom - temp.top;
					}

				}
				//세로가 넓다 = 좌, 우 에서 충돌했다
				else {
					//left가 같다 = 우측에서 충돌했다
					if (playerRect.left == temp.left) {
						//우로 밀어줘야함 +
						pt.x += temp.right - temp.left;
					}
					else {
						//좌로 밀어줘야함 -
						pt.x -= temp.right - temp.left;
					}
				}
				return true;
			}
		}
	}
	return false;
}

void mapManager::collision(RECT rc)
{
	
}

void mapManager::stageClearCheck()
{
	bool isClear = true;
	for (vector<enemy*>::iterator iter = ENEMYMANAGER->getShowEnemyVector().begin(); iter != ENEMYMANAGER->getShowEnemyVector().end();++iter) {
		//죽지 않은 것이 있으면 false
		if ((*iter)->getInfo().state != E_DEAD) {
			isClear = false;
		}
	}
}

void mapManager::setRandomMap()
{
	setRandomStage(stage_first);
	random();
}

void mapManager::render(HDC hdc)
{
	
}
void mapManager::RectRender(HDC hdc)
{
	for (int i = 0; i < TILEX; ++i) {
		for (int j = 0; j < TILEY; ++j) {
			if (_tiles[i][j].wall == WALL_NONE) {
				continue;
			}
			else {
				Rectangle(hdc,_tiles[i][j].rc);
			}
		}
	}
}
void mapManager::stretchMapRender(HDC hdc)
{
	for (int i = 0; i < TILEX; ++i) {
		for (int j = 0; j < TILEY; ++j) {

			IMAGEMANAGER->findImage("mapTiles")->frameRender(
				hdc, i * TILESIZE, j * TILESIZE,
				_tiles[i][j].terrainFrameX,
				_tiles[i][j].terrainFrameY);
		}
	}
	for (int i = 0; i < TILEX; ++i) {
		for (int j = 0; j < TILEY; ++j) {
			if (_tiles[i][j].wall == WALL_NONE)
				continue;

			IMAGEMANAGER->findImage("mapWall")->frameRender(
				hdc, i * TILESIZE, j * TILESIZE,
				_tiles[i][j].wallFrameX,
				_tiles[i][j].wallFrameY);
		}
	}
	for (int i = 0; i < TILEX; ++i) {
		for (int j = 0; j < TILEY; ++j) {
			if (_tiles[i][j].obj == OBJ_NONE)
				continue;

			if (_tiles[i][j].obj != OBJ1_SHD &&
				_tiles[i][j].obj != OBJ2_SHD &&
				_tiles[i][j].obj != OBJ3_SHD)
			{
				IMAGEMANAGER->findImage("mapObj")->frameRender(
					hdc, i * TILESIZE, j * TILESIZE,
					_tiles[i][j].objFrameX,
					_tiles[i][j].objFrameY);
			}
			else
			{

				IMAGEMANAGER->findImage("mapObj")->alphaRender(
					hdc, i * TILESIZE, j * TILESIZE,
					_tiles[i][j].objFrameX,
					_tiles[i][j].objFrameY,
					TILESIZE, TILESIZE, 100);
			}


		}
	}
	

	if (PLAYERMANAGER->getPlayer() != nullptr) {
		IMAGEMANAGER->findImage("playerset")->frameRender(
			hdc,
			PLAYERMANAGER->getPlayer()->getPt().x,
			PLAYERMANAGER->getPlayer()->getPt().y,
			(int)PLAYERMANAGER->getPlayerType(), 0);

	}
	for (enemy* e : ENEMYMANAGER->getEnemys("custom")) {
		tagCurrentTile temp = getEnemyTileset(e->getEnemyType());

		temp.img->frameRender(hdc, e->getInfo().pt.x, e->getInfo().pt.y,temp.x,temp.y);
	}
}

void mapManager::strectchSceneRender(HDC hdc)
{

	for (int i = 0; i < TILEX; ++i) {
		for (int j = 0; j < TILEY; ++j) {

			IMAGEMANAGER->findImage("mapTiles")->frameRender(
				hdc, i * TILESIZE, j * TILESIZE,
				_tiles[i][j].terrainFrameX,
				_tiles[i][j].terrainFrameY);
		}
	}
	for (int i = 0; i < TILEX; ++i) {
		for (int j = 0; j < TILEY; ++j) {
			if (_tiles[i][j].wall == WALL_NONE)
				continue;

			IMAGEMANAGER->findImage("mapWall")->frameRender(
				hdc, i * TILESIZE, j * TILESIZE,
				_tiles[i][j].wallFrameX,
				_tiles[i][j].wallFrameY);
		}
	}
	for (int i = 0; i < TILEX; ++i) {
		for (int j = 0; j < TILEY; ++j) {
			if (_tiles[i][j].obj == OBJ_NONE)
				continue;

			if (_tiles[i][j].obj != OBJ1_SHD &&
				_tiles[i][j].obj != OBJ2_SHD &&
				_tiles[i][j].obj != OBJ3_SHD)
			{
				IMAGEMANAGER->findImage("mapObj")->frameRender(
					hdc, i * TILESIZE, j * TILESIZE,
					_tiles[i][j].objFrameX,
					_tiles[i][j].objFrameY);
			}
			else
			{

				IMAGEMANAGER->findImage("mapObj")->alphaRender(
					hdc, i * TILESIZE, j * TILESIZE,
					_tiles[i][j].objFrameX,
					_tiles[i][j].objFrameY,
					TILESIZE, TILESIZE, 100);
			}
		}
	}
}
void mapManager::mapRender(HDC hdc)
{
	for (int i = 0; i < width_count; ++i) {
		for (int j = 0; j < height_count; ++j) {

			IMAGEMANAGER->findImage("mapTiles")->frameRender(
			hdc, _showTile[i][j].rc.left, _showTile[i][j].rc.top,
				_tiles[_showTile[i][j].pt.x][_showTile[i][j].pt.y].terrainFrameX,
				_tiles[_showTile[i][j].pt.x][_showTile[i][j].pt.y].terrainFrameY);
		}
	}
	for (int i = 0; i < width_count; ++i) {
		for (int j = 0; j < height_count; ++j) {
			if (_tiles[_showTile[i][j].pt.x][_showTile[i][j].pt.y].wall == WALL_NONE)
				continue;

			IMAGEMANAGER->findImage("mapWall")->frameRender(
				hdc, _showTile[i][j].rc.left, _showTile[i][j].rc.top,
				_tiles[_showTile[i][j].pt.x][_showTile[i][j].pt.y].wallFrameX,
				_tiles[_showTile[i][j].pt.x][_showTile[i][j].pt.y].wallFrameY);
		}
	}
	for (int i = 0; i < width_count; ++i) {
		for (int j = 0; j < height_count; ++j) {
			if (_tiles[_showTile[i][j].pt.x][_showTile[i][j].pt.y].obj == OBJ_NONE)
				continue;

				IMAGEMANAGER->findImage("mapObj")->frameRender(
					hdc, _showTile[i][j].rc.left, _showTile[i][j].rc.top,
					_tiles[_showTile[i][j].pt.x][_showTile[i][j].pt.y].objFrameX,
					_tiles[_showTile[i][j].pt.x][_showTile[i][j].pt.y].objFrameY);
			
		}
	}
}

void mapManager::mapToolRender(HDC hdc)
{
	//Sample tileSet
	if (_Select == DrawTerrain) {
		IMAGEMANAGER->render("samTiles", hdc, WINSIZEX - IMAGEMANAGER->findImage("samTiles")->getWidth() - 60, 50);
	}
	else if (_Select == DrawWall) {
		IMAGEMANAGER->render("samWall", hdc, WINSIZEX - IMAGEMANAGER->findImage("samWall")->getWidth() - 60, 50);
	}
	else if (_Select == DrawObj) {
		IMAGEMANAGER->render("mapObj", hdc, WINSIZEX - IMAGEMANAGER->findImage("mapObj")->getWidth() - 60, 50);
	}
	else if (_Select == DrawPlayer) {
		IMAGEMANAGER->render("playerset", hdc, WINSIZEX - IMAGEMANAGER->findImage("playerset")->getWidth() - 60, 50);
	}
	else if (_Select == DrawEnemy) {
		IMAGEMANAGER->render("enemyset", hdc, WINSIZEX - IMAGEMANAGER->findImage("enemyset")->getWidth() - 60, 50);
	}
	else if (_Select == DrawBoss) {
		IMAGEMANAGER->render("bossset", hdc, WINSIZEX - IMAGEMANAGER->findImage("bossset")->getWidth() - 60, 50);
	}

	//타일 위에 마우스가 올라가면 선을 그려줌
	for (int i = 0; i < width_count; ++i) {
		for (int j = 0; j < height_count; ++j) {
			if (PtInRect(&_showTile[i][j].rc, _ptMouse)) {
				if (_Select == DrawTerrain) {
					//alpharender 수정 필요 (반만나옴)
					IMAGEMANAGER->findImage("mapTiles")->alphaRender(
						hdc,
						_showTile[i][j].rc.left,
						_showTile[i][j].rc.top,
						_currentTile.x,
						_currentTile.y,
						_showTile[i][j].rc.right - _showTile[i][j].rc.left,
						_showTile[i][j].rc.bottom - _showTile[i][j].rc.top, 100
					);
				}
				else if (_Select == DrawWall) {
					//alpharender 수정 필요 (반만나옴)
					IMAGEMANAGER->findImage("mapWall")->alphaRender(
						hdc,
						_showTile[i][j].rc.left,
						_showTile[i][j].rc.top,
						_currentTile.x,
						_currentTile.y,
						_showTile[i][j].rc.right - _showTile[i][j].rc.left,
						_showTile[i][j].rc.bottom - _showTile[i][j].rc.top, 100
					);
				}
				else if (_Select == DrawObj) {
					//alpharender 수정 필요 (반만나옴)
					IMAGEMANAGER->findImage("mapObj")->alphaRender(
						hdc,
						_showTile[i][j].rc.left,
						_showTile[i][j].rc.top,
						_currentTile.x,
						_currentTile.y,
						_showTile[i][j].rc.right - _showTile[i][j].rc.left,
						_showTile[i][j].rc.bottom - _showTile[i][j].rc.top, 100
					);
				}
				else if (_Select == DrawPlayer) {
					//alpharender 수정 필요 (반만나옴)
					IMAGEMANAGER->findImage("playerset")->alphaRender(
						hdc,
						_showTile[i][j].rc.left,
						_showTile[i][j].rc.top,
						_currentTile.x,
						_currentTile.y,
						_showTile[i][j].rc.right - _showTile[i][j].rc.left,
						_showTile[i][j].rc.bottom - _showTile[i][j].rc.top, 100
					);
				}
				LineMake(hdc, _showTile[i][j].rc.left, _showTile[i][j].rc.top, _showTile[i][j].rc.left, _showTile[i][j].rc.bottom);
				LineMake(hdc, _showTile[i][j].rc.right, _showTile[i][j].rc.top, _showTile[i][j].rc.right, _showTile[i][j].rc.bottom);
				LineMake(hdc, _showTile[i][j].rc.left, _showTile[i][j].rc.top, _showTile[i][j].rc.right, _showTile[i][j].rc.top);
				LineMake(hdc, _showTile[i][j].rc.left, _showTile[i][j].rc.bottom, _showTile[i][j].rc.right, _showTile[i][j].rc.bottom);
			}
		}
	}
	//minimap
	minimapRender(hdc);
}

void mapManager::minimapRender(HDC hdc)
{
	//배율
	int minimapSize = 5;

	HPEN pen = CreatePen(PS_SOLID,1,RGB(0,255,0));
	HPEN oldPen = (HPEN)SelectObject(hdc,pen);
	//전체 맵
	LineMake(hdc, 0, 0, TILEX * minimapSize, 0);
	LineMake(hdc, 0, 0, 0, TILEY * minimapSize);
	LineMake(hdc, TILEX * minimapSize, TILEY * minimapSize, TILEX * minimapSize, 0);
	LineMake(hdc, TILEX * minimapSize, TILEY * minimapSize, 0, TILEY * minimapSize);
	DeleteObject(pen);

	pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, pen);
	//미니 맵
	LineMake(hdc, _pt.x * minimapSize, _pt.y * minimapSize, (_pt.x + width_count) * minimapSize, _pt.y * minimapSize);
	LineMake(hdc, _pt.x * minimapSize, _pt.y * minimapSize, _pt.x * minimapSize, (_pt.y + height_count) * minimapSize);
	LineMake(hdc, (_pt.x + width_count) * minimapSize, (_pt.y + height_count) * minimapSize, _pt.x * minimapSize, (_pt.y + height_count) * minimapSize);
	LineMake(hdc, (_pt.x + width_count) * minimapSize, (_pt.y + height_count) * minimapSize, (_pt.x + width_count) * minimapSize, _pt.y * minimapSize);
	DeleteObject(pen);
}

void mapManager::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("saveMap1.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);
}

void mapManager::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("saveMap1.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}

void mapManager::load(LPCSTR strKey)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(strKey, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}

void mapManager::eraser()
{
	for (int i = 0; i < width_count; ++i) {
		for (int j = 0; j < height_count; ++j) {
			if (_Select == Eraser)
			{
				if (PtInRect(&_tiles[i][j].rc, _ptMouse))
				{
					_tiles[i][j].objFrameX = NULL;
					_tiles[i][j].objFrameY = NULL;
					_tiles[i][j].wallFrameX = NULL;
					_tiles[i][j].wallFrameY = NULL;
					_tiles[i][j].obj = OBJ_NONE;
					_tiles[i][j].wall = WALL_NONE;
				}
			}
		}
	}
}

void mapManager::emptymap()
{
	for (int i = 0; i < TILEX; ++i) {
		for (int j = 0; j < TILEY; ++j) {

			_tiles[i][j].wall = WALL_NONE;
			_tiles[i][j].obj = OBJ_NONE;
			ENEMYMANAGER->remove();
			ITEMMANAGER->remove();
			
		}
	}
}

void mapManager::random()
{
	srand(time(NULL));

	//맵 지우기
	emptymap();

	//stage 초기화
	for (int i = 0; i < TILEX; ++i) {
		for (int j = 0; j < TILEY; ++j) {
			//stage1
			if (_rnd == 0)
			{
				//tiles
				_tiles[i][j].terrain = TR_C;
				_tiles[i][j].terrainFrameX = 0;
				_tiles[i][j].terrainFrameY = 0;

				//wall 기본
				_tiles[i][j].wall = W_ROOF;
				_tiles[i][j].wallFrameX = 1;
				_tiles[i][j].wallFrameY = 1;


			}
			//stage 2
			else if (_rnd == 1)
			{

				_tiletemp = RND->getInt(30);

				//tiles
				if (_tiletemp <= 23)
				{
					_tiles[i][j].terrain = T2R_C;
					_tiles[i][j].terrainFrameX = 0;
					_tiles[i][j].terrainFrameY = 2;
				}
				else if (_tiletemp == 24)
				{
					_tiles[i][j].terrain = T2R_C2;
					_tiles[i][j].terrainFrameX = 1;
					_tiles[i][j].terrainFrameY = 2;
				}
				else if (_tiletemp == 25)
				{
					_tiles[i][j].terrain = T2R_C3;
					_tiles[i][j].terrainFrameX = 2;
					_tiles[i][j].terrainFrameY = 2;
				}
				else if (_tiletemp == 26)
				{
					_tiles[i][j].terrain = T2R_C4;
					_tiles[i][j].terrainFrameX = 3;
					_tiles[i][j].terrainFrameY = 2;
				}
				else if (_tiletemp == 27)
				{
					_tiles[i][j].terrain = T2R_C5;
					_tiles[i][j].terrainFrameX = 4;
					_tiles[i][j].terrainFrameY = 2;
				}
				else if (_tiletemp == 28)
				{
					_tiles[i][j].terrain = T2R_P;
					_tiles[i][j].terrainFrameX = 0;
					_tiles[i][j].terrainFrameY = 3;
				}
				else if (_tiletemp == 29)
				{
					_tiles[i][j].terrain = T2R_P2;
					_tiles[i][j].terrainFrameX = 1;
					_tiles[i][j].terrainFrameY = 3;
				}


				_walltemp = RND->getInt(20);

				//wall 테두리

				if (_walltemp <= 17)
				{
					_tiles[i][j].wall = W2_R;
					_tiles[i][j].wallFrameX = 3;
					_tiles[i][j].wallFrameY = 3;


				}
				else if (_walltemp == 18)
				{
					_tiles[i][j].wall = W2_R2;
					_tiles[i][j].wallFrameX = 4;
					_tiles[i][j].wallFrameY = 3;


				}
				else if (_walltemp == 19)
				{
					_tiles[i][j].wall = W2_R3;
					_tiles[i][j].wallFrameX = 5;
					_tiles[i][j].wallFrameY = 3;
				}



			}
			//stage 3
			else if (_rnd == 2)
			{
				for (int i = 0; i < TILEX; ++i) {
					for (int j = 0; j < TILEY; ++j) {
						//tiles
						_tiles[i][j].terrain = T3R_C;
						_tiles[i][j].terrainFrameX = 2;
						_tiles[i][j].terrainFrameY = 4;

						//wall 테두리
						_tiles[i][j].wall = W3_C2;
						_tiles[i][j].wallFrameX = 3;
						_tiles[i][j].wallFrameY = 5;


					}
				}


			}
		}
	}

	//랜덤 시작점 3~5
	_xtemp = RND->getInt(3) + 3;
	_ytemp = RND->getInt(3) + 3;

	_x2temp = RND->getInt(3) + 6;
	_y2temp = RND->getInt(3) + 6;

	_tiles[_xtemp][_ytemp].wallFrameX = NULL;
	_tiles[_xtemp][_ytemp].wallFrameY = NULL;
	_tiles[_xtemp][_ytemp].wall = WALL_NONE;


	//다른 타일 찍어줄 중심점
	_tiles[_x2temp][_y2temp].wallFrameX = NULL;
	_tiles[_x2temp][_y2temp].wallFrameY = NULL;
	_tiles[_x2temp][_y2temp].wall = WALL_NONE;

	_tiles[_x2temp + 10][_y2temp + 10].wallFrameX = NULL;
	_tiles[_x2temp + 10][_y2temp + 10].wallFrameY = NULL;
	_tiles[_x2temp + 10][_y2temp + 10].wall = WALL_NONE;

	_tiles[_x2temp + 15][_y2temp + 15].wallFrameX = NULL;
	_tiles[_x2temp + 15][_y2temp + 15].wallFrameY = NULL;
	_tiles[_x2temp + 15][_y2temp + 15].wall = WALL_NONE;


	//지형 만들기

	for (int i = 3; i < TILEX - 3; ++i) {
		for (int j = 3; j < TILEY - 3; ++j) {

			//stage1
			if (_rnd == 0)
			{
				//지형 만들기
				_tiles[_xtemp][_ytemp].terrain = TR_C;
				_tiles[_xtemp][_ytemp].terrainFrameX = 0;
				_tiles[_xtemp][_ytemp].terrainFrameY = 0;
				_objtemp = RND->getInt(100);

				_tiles[_x2temp][_y2temp].terrain = TR2_C;
				_tiles[_x2temp][_y2temp].terrainFrameX = 2;
				_tiles[_x2temp][_y2temp].terrainFrameY = 0;
				_tiles[_x2temp + 10][_y2temp + 10].terrain = TR2_C;
				_tiles[_x2temp + 10][_y2temp + 10].terrainFrameX = 2;
				_tiles[_x2temp + 10][_y2temp + 10].terrainFrameY = 0;
				_tiles[_x2temp + 15][_y2temp + 15].terrain = TR2_C;
				_tiles[_x2temp + 15][_y2temp + 15].terrainFrameX = 2;
				_tiles[_x2temp + 15][_y2temp + 15].terrainFrameY = 0;



				if (_tiles[i][j].wall == WALL_NONE)
				{

					_walltemp = RND->getInt(40);

					if (_walltemp < 5)
					{
						if (_tiles[i - 1][j].wall != WALL_NONE)
						{
							_tiles[i - 1][j].wallFrameX = NULL;
							_tiles[i - 1][j].wallFrameY = NULL;
							_tiles[i - 1][j].wall = WALL_NONE;

							_tiles[i - 1][j].terrain = TR_C;
							_tiles[i - 1][j].terrainFrameX = 0;
							_tiles[i - 1][j].terrainFrameY = 0;
						}
						if (_tiles[i + 1][j].wall != WALL_NONE)
						{
							_tiles[i + 1][j].wallFrameX = NULL;
							_tiles[i + 1][j].wallFrameY = NULL;
							_tiles[i + 1][j].wall = WALL_NONE;

							_tiles[i + 1][j].terrain = TR_C;
							_tiles[i + 1][j].terrainFrameX = 0;
							_tiles[i + 1][j].terrainFrameY = 0;
						}
						if (_tiles[i][j - 1].wall != WALL_NONE)
						{
							_tiles[i][j - 1].wallFrameX = NULL;
							_tiles[i][j - 1].wallFrameY = NULL;
							_tiles[i][j - 1].wall = WALL_NONE;

							_tiles[i][j - 1].terrain = TR_C;
							_tiles[i][j - 1].terrainFrameX = 0;
							_tiles[i][j - 1].terrainFrameY = 0;
						}
						if (_tiles[i][j + 1].wall != WALL_NONE)
						{
							_tiles[i][j + 1].wallFrameX = NULL;
							_tiles[i][j + 1].wallFrameY = NULL;
							_tiles[i][j + 1].wall = WALL_NONE;

							_tiles[i][j + 1].terrain = TR_C;
							_tiles[i][j + 1].terrainFrameX = 0;
							_tiles[i][j + 1].terrainFrameY = 0;
						}
					}
					else if (_walltemp < 11)
					{
						if (_tiles[i - 1][j].wall != WALL_NONE)
						{
							_tiles[i - 1][j].wallFrameX = NULL;
							_tiles[i - 1][j].wallFrameY = NULL;
							_tiles[i - 1][j].wall = WALL_NONE;

							_tiles[i - 1][j].terrain = TR_C;
							_tiles[i - 1][j].terrainFrameX = 0;
							_tiles[i - 1][j].terrainFrameY = 0;
						}
						if (_tiles[i + 1][j].wall != WALL_NONE)
						{
							_tiles[i + 1][j].wallFrameX = NULL;
							_tiles[i + 1][j].wallFrameY = NULL;
							_tiles[i + 1][j].wall = WALL_NONE;

							_tiles[i + 1][j].terrain = TR_C;
							_tiles[i + 1][j].terrainFrameX = 0;
							_tiles[i + 1][j].terrainFrameY = 0;
						}
					}
					else if (_walltemp < 17)
					{
						if (_tiles[i][j - 1].wall != WALL_NONE)
						{
							_tiles[i][j - 1].wallFrameX = NULL;
							_tiles[i][j - 1].wallFrameY = NULL;
							_tiles[i][j - 1].wall = WALL_NONE;

							_tiles[i][j - 1].terrain = TR_C;
							_tiles[i][j - 1].terrainFrameX = 0;
							_tiles[i][j - 1].terrainFrameY = 0;
						}
						if (_tiles[i][j + 1].wall != WALL_NONE)
						{
							_tiles[i][j + 1].wallFrameX = NULL;
							_tiles[i][j + 1].wallFrameY = NULL;
							_tiles[i][j + 1].wall = WALL_NONE;

							_tiles[i][j + 1].terrain = TR_C;
							_tiles[i][j + 1].terrainFrameX = 0;
							_tiles[i][j + 1].terrainFrameY = 0;
						}
					}
					else if (_walltemp < 23)
					{
						if (_tiles[i - 1][j].wall != WALL_NONE)
						{
							_tiles[i - 1][j].wallFrameX = NULL;
							_tiles[i - 1][j].wallFrameY = NULL;
							_tiles[i - 1][j].wall = WALL_NONE;

							_tiles[i - 1][j].terrain = TR_C;
							_tiles[i - 1][j].terrainFrameX = 0;
							_tiles[i - 1][j].terrainFrameY = 0;
						}
						if (_tiles[i][j + 1].wall != WALL_NONE)
						{
							_tiles[i][j + 1].wallFrameX = NULL;
							_tiles[i][j + 1].wallFrameY = NULL;
							_tiles[i][j + 1].wall = WALL_NONE;

							_tiles[i][j + 1].terrain = TR_C;
							_tiles[i][j + 1].terrainFrameX = 0;
							_tiles[i][j + 1].terrainFrameY = 0;
						}

					}
					else if (_walltemp < 31)
					{
						if (_tiles[i + 1][j].wall != WALL_NONE)
						{
							_tiles[i + 1][j].wallFrameX = NULL;
							_tiles[i + 1][j].wallFrameY = NULL;
							_tiles[i + 1][j].wall = WALL_NONE;

							_tiles[i + 1][j].terrain = TR_C;
							_tiles[i + 1][j].terrainFrameX = 0;
							_tiles[i + 1][j].terrainFrameY = 0;
						}
						if (_tiles[i][j - 1].wall != WALL_NONE)
						{
							_tiles[i][j - 1].wallFrameX = NULL;
							_tiles[i][j - 1].wallFrameY = NULL;
							_tiles[i][j - 1].wall = WALL_NONE;

							_tiles[i][j - 1].terrain = TR_C;
							_tiles[i][j - 1].terrainFrameX = 0;
							_tiles[i][j - 1].terrainFrameY = 0;
						}
					}
					else if (_walltemp < 40)
					{
						if (_tiles[i + 1][j].wall != WALL_NONE)
						{
							_tiles[i + 1][j].wallFrameX = NULL;
							_tiles[i + 1][j].wallFrameY = NULL;
							_tiles[i + 1][j].wall = WALL_NONE;

							_tiles[i + 1][j].terrain = TR_C;
							_tiles[i + 1][j].terrainFrameX = 0;
							_tiles[i + 1][j].terrainFrameY = 0;
						}
						if (_tiles[i][j + 1].wall != WALL_NONE)
						{
							_tiles[i][j + 1].wallFrameX = NULL;
							_tiles[i][j + 1].wallFrameY = NULL;
							_tiles[i][j + 1].wall = WALL_NONE;

							_tiles[i][j + 1].terrain = TR_C;
							_tiles[i][j + 1].terrainFrameX = 0;
							_tiles[i][j + 1].terrainFrameY = 0;
						}
					}
				}


				//OBJ 만들기

				if (_objtemp < 30)
				{
					if (_tiles[i][j].wall == WALL_NONE)
					{
						if (_objtemp == 26)
						{
							_tiles[i][j].obj = OBJ_BLOCK5;
							_tiles[i][j].objFrameX = 0;
							_tiles[i][j].objFrameY = 1;
						}
						else if (_objtemp == 27)
						{
							_tiles[i][j].obj = OBJ_BLOCK6;
							_tiles[i][j].objFrameX = 1;
							_tiles[i][j].objFrameY = 1;
						}
						else if (_objtemp == 28)
						{
							_tiles[i][j].obj = OBJ_BLOCK7;
							_tiles[i][j].objFrameX = 2;
							_tiles[i][j].objFrameY = 1;
						}
						else if (_objtemp == 29)
						{
							_tiles[i][j].obj = OBJ_BLOCK8;
							_tiles[i][j].objFrameX = 3;
							_tiles[i][j].objFrameY = 1;
						}
						else
						{
							_tiles[i][j].objFrameX = NULL;
							_tiles[i][j].objFrameY = NULL;
							_tiles[i][j].obj = OBJ_NONE;
						}
					}
					else if (_tiles[i][j].wall != WALL_NONE)
					{
						if (_objtemp == 3 && _tiles[i][j].wall != W_2BT && _tiles[i][j].wall != W_3B && _tiles[i][j].wall != W_3L &&
							_tiles[i][j].wall != W_3R && _tiles[i][j].wall != W_B && _tiles[i][j].wall != W_LB && _tiles[i][j].wall != W_RB && _tiles[i][j].wall != W_4)
						{
							_tiles[i][j].obj = OBJ_BLOCK1;
							_tiles[i][j].objFrameX = 0;
							_tiles[i][j].objFrameY = 0;
						}
						else if (_objtemp == 7 && _tiles[i][j].wall != W_2BT && _tiles[i][j].wall != W_3B && _tiles[i][j].wall != W_3L &&
							_tiles[i][j].wall != W_3R && _tiles[i][j].wall != W_B && _tiles[i][j].wall != W_LB && _tiles[i][j].wall != W_RB && _tiles[i][j].wall != W_4)
						{
							_tiles[i][j].obj = OBJ_BLOCK2;
							_tiles[i][j].objFrameX = 1;
							_tiles[i][j].objFrameY = 0;
						}
						else
						{
							_tiles[i][j].objFrameX = NULL;
							_tiles[i][j].objFrameY = NULL;
							_tiles[i][j].obj = OBJ_NONE;
						}
					}
				}
			}


			//stage2
			else if (_rnd == 1)
			{
				_tiles[_xtemp][_ytemp].terrain = T2R_C;
				_tiles[_xtemp][_ytemp].terrainFrameX = 0;
				_tiles[_xtemp][_ytemp].terrainFrameY = 2;
				_objtemp = RND->getInt(100);
				if (_tiles[i][j].wall == WALL_NONE)
				{
					_tiletemp = RND->getInt(25);
					_walltemp = RND->getInt(40);

					if (_walltemp < 5)
					{
						if (_tiles[i - 1][j].wall != WALL_NONE)
						{
							_tiles[i - 1][j].wallFrameX = NULL;
							_tiles[i - 1][j].wallFrameY = NULL;
							_tiles[i - 1][j].wall = WALL_NONE;

							if (_tiletemp < 23)
							{
								_tiles[i - 1][j].terrain = T2R_C;
								_tiles[i - 1][j].terrainFrameX = 0;
								_tiles[i - 1][j].terrainFrameY = 2;
							}
							else if (_tiletemp == 24)
							{
								_tiles[i - 1][j].terrain = T2R_C2;
								_tiles[i - 1][j].terrainFrameX = 1;
								_tiles[i - 1][j].terrainFrameY = 2;
							}
						}
						if (_tiles[i + 1][j].wall != WALL_NONE)
						{
							_tiles[i + 1][j].wallFrameX = NULL;
							_tiles[i + 1][j].wallFrameY = NULL;
							_tiles[i + 1][j].wall = WALL_NONE;

							if (_tiletemp < 24)
							{
								_tiles[i + 1][j].terrain = T2R_C;
								_tiles[i + 1][j].terrainFrameX = 0;
								_tiles[i + 1][j].terrainFrameY = 2;
							}
							else if (_tiletemp == 24)
							{
								_tiles[i + 1][j].terrain = T2R_C3;
								_tiles[i + 1][j].terrainFrameX = 2;
								_tiles[i + 1][j].terrainFrameY = 2;
							}
						}
						if (_tiles[i][j - 1].wall != WALL_NONE)
						{
							_tiles[i][j - 1].wallFrameX = NULL;
							_tiles[i][j - 1].wallFrameY = NULL;
							_tiles[i][j - 1].wall = WALL_NONE;

							if (_tiletemp < 24)
							{
								_tiles[i][j - 1].terrain = T2R_C;
								_tiles[i][j - 1].terrainFrameX = 0;
								_tiles[i][j - 1].terrainFrameY = 2;
							}
							else if (_tiletemp == 24)
							{
								_tiles[i][j - 1].terrain = T2R_C;
								_tiles[i][j - 1].terrainFrameX = 0;
								_tiles[i][j - 1].terrainFrameY = 2;
							}
						}

						if (_tiles[i][j + 1].wall != WALL_NONE)
						{
							_tiles[i][j + 1].wallFrameX = NULL;
							_tiles[i][j + 1].wallFrameY = NULL;
							_tiles[i][j + 1].wall = WALL_NONE;

							if (_tiletemp < 24)
							{
								_tiles[i][j + 1].terrain = T2R_C;
								_tiles[i][j + 1].terrainFrameX = 0;
								_tiles[i][j + 1].terrainFrameY = 2;
							}
							else if (_tiletemp == 24)
							{
								_tiles[i][j + 1].terrain = T2R_C;
								_tiles[i][j + 1].terrainFrameX = 0;
								_tiles[i][j + 1].terrainFrameY = 2;
							}
						}
					}
					else if (_walltemp < 11)
					{
						if (_tiles[i - 1][j].wall != WALL_NONE)
						{
							_tiles[i - 1][j].wallFrameX = NULL;
							_tiles[i - 1][j].wallFrameY = NULL;
							_tiles[i - 1][j].wall = WALL_NONE;

							if (_tiletemp < 24)
							{
								_tiles[i - 1][j].terrain = T2R_C;
								_tiles[i - 1][j].terrainFrameX = 0;
								_tiles[i - 1][j].terrainFrameY = 2;
							}
							else if (_tiletemp == 24)
							{
								_tiles[i - 1][j].terrain = T2R_P;
								_tiles[i - 1][j].terrainFrameX = 0;
								_tiles[i - 1][j].terrainFrameY = 3;
							}
						}
						if (_tiles[i + 1][j].wall != WALL_NONE)
						{
							_tiles[i + 1][j].wallFrameX = NULL;
							_tiles[i + 1][j].wallFrameY = NULL;
							_tiles[i + 1][j].wall = WALL_NONE;

							if (_tiletemp < 24)
							{
								_tiles[i + 1][j].terrain = T2R_C;
								_tiles[i + 1][j].terrainFrameX = 0;
								_tiles[i + 1][j].terrainFrameY = 2;
							}
							else if (_tiletemp == 24)
							{
								_tiles[i + 1][j].terrain = T2R_P2;
								_tiles[i + 1][j].terrainFrameX = 2;
								_tiles[i + 1][j].terrainFrameY = 2;
							}
						}
					}
					else if (_walltemp < 17)
					{
						if (_tiles[i][j - 1].wall != WALL_NONE)
						{
							_tiles[i][j - 1].wallFrameX = NULL;
							_tiles[i][j - 1].wallFrameY = NULL;
							_tiles[i][j - 1].wall = WALL_NONE;

							if (_tiletemp < 24)
							{
								_tiles[i][j - 1].terrain = T2R_C;
								_tiles[i][j - 1].terrainFrameX = 0;
								_tiles[i][j - 1].terrainFrameY = 2;
							}
							else if (_tiletemp == 24)
							{
								_tiles[i][j - 1].terrain = T2R_P3;
								_tiles[i][j - 1].terrainFrameX = 2;
								_tiles[i][j - 1].terrainFrameY = 2;
							}
						}

						if (_tiles[i][j + 1].wall != WALL_NONE)
						{
							_tiles[i][j + 1].wallFrameX = NULL;
							_tiles[i][j + 1].wallFrameY = NULL;
							_tiles[i][j + 1].wall = WALL_NONE;

							if (_tiletemp < 24)
							{
								_tiles[i][j + 1].terrain = T2R_C;
								_tiles[i][j + 1].terrainFrameX = 0;
								_tiles[i][j + 1].terrainFrameY = 2;
							}
							else if (_tiletemp == 24)
							{
								_tiles[i][j + 1].terrain = T2R_C4;
								_tiles[i][j + 1].terrainFrameX = 3;
								_tiles[i][j + 1].terrainFrameY = 2;
							}
						}
					}
					else if (_walltemp < 23)
					{
						if (_tiles[i - 1][j].wall != WALL_NONE)
						{
							_tiles[i - 1][j].wallFrameX = NULL;
							_tiles[i - 1][j].wallFrameY = NULL;
							_tiles[i - 1][j].wall = WALL_NONE;

							if (_tiletemp < 24)
							{
								_tiles[i - 1][j].terrain = T2R_C;
								_tiles[i - 1][j].terrainFrameX = 0;
								_tiles[i - 1][j].terrainFrameY = 2;
							}
							else if (_tiletemp == 24)
							{
								_tiles[i - 1][j].terrain = T2R_P;
								_tiles[i - 1][j].terrainFrameX = 0;
								_tiles[i - 1][j].terrainFrameY = 3;
							}
						}

						if (_tiles[i][j + 1].wall != WALL_NONE)
						{
							_tiles[i][j + 1].wallFrameX = NULL;
							_tiles[i][j + 1].wallFrameY = NULL;
							_tiles[i][j + 1].wall = WALL_NONE;

							if (_tiletemp < 18)
							{
								_tiles[i][j + 1].terrain = T2R_C;
								_tiles[i][j + 1].terrainFrameX = 0;
								_tiles[i][j + 1].terrainFrameY = 2;
							}
							else if (_tiletemp == 24)
							{
								_tiles[i][j + 1].terrain = T2R_C4;
								_tiles[i][j + 1].terrainFrameX = 3;
								_tiles[i][j + 1].terrainFrameY = 2;
							}
						}
					}
					else if (_walltemp < 31)
					{
						if (_tiles[i + 1][j].wall != WALL_NONE)
						{
							_tiles[i + 1][j].wallFrameX = NULL;
							_tiles[i + 1][j].wallFrameY = NULL;
							_tiles[i + 1][j].wall = WALL_NONE;

							if (_tiletemp < 24)
							{
								_tiles[i + 1][j].terrain = T2R_C;
								_tiles[i + 1][j].terrainFrameX = 0;
								_tiles[i + 1][j].terrainFrameY = 2;
							}
							else if (_tiletemp == 24)
							{
								_tiles[i + 1][j].terrain = T2R_P;
								_tiles[i + 1][j].terrainFrameX = 0;
								_tiles[i + 1][j].terrainFrameY = 3;
							}
						}
						if (_tiles[i][j - 1].wall != WALL_NONE)
						{
							_tiles[i][j - 1].wallFrameX = NULL;
							_tiles[i][j - 1].wallFrameY = NULL;
							_tiles[i][j - 1].wall = WALL_NONE;


							_tiles[i][j - 1].terrain = T2R_C;
							_tiles[i][j - 1].terrainFrameX = 0;
							_tiles[i][j - 1].terrainFrameY = 2;
						}
					}
					else if (_walltemp < 40)
					{
						if (_tiles[i + 1][j].wall != WALL_NONE)
						{
							_tiles[i + 1][j].wallFrameX = NULL;
							_tiles[i + 1][j].wallFrameY = NULL;
							_tiles[i + 1][j].wall = WALL_NONE;


							_tiles[i - 1][j].terrain = T2R_C;
							_tiles[i - 1][j].terrainFrameX = 0;
							_tiles[i - 1][j].terrainFrameY = 2;
						}
						if (_tiles[i][j + 1].wall != WALL_NONE)
						{
							_tiles[i][j + 1].wallFrameX = NULL;
							_tiles[i][j + 1].wallFrameY = NULL;
							_tiles[i][j + 1].wall = WALL_NONE;


							_tiles[i][j + 1].terrain = T2R_C;
							_tiles[i][j + 1].terrainFrameX = 0;
							_tiles[i][j + 1].terrainFrameY = 2;

						}
					}

				}
				//OBJ
				if (_objtemp < 30)
				{
					if (_tiles[i][j].wall == WALL_NONE)
					{
						if (_tiles[i - 1][j].wall == W2_R && _tiles[i + 1][j].wall == WALL_NONE && _objtemp == 21)
						{
							_tiles[i][j].obj = OBJ2_BLOCK3;
							_tiles[i][j].objFrameX = 2;
							_tiles[i][j].objFrameY = 2;
						}
						else if (_tiles[i + 1][j].wall == W2_R && _tiles[i - 1][j].wall == WALL_NONE && _objtemp == 22)
						{
							_tiles[i][j].obj = OBJ2_BLOCK4;
							_tiles[i][j].objFrameX = 3;
							_tiles[i][j].objFrameY = 2;
						}
						else if (_objtemp == 26 && _tiles[i][j + 1].wall == WALL_NONE && _tiles[i - 1][j].wall == WALL_NONE && _tiles[i + 1][j].wall == WALL_NONE && _tiles[i][j - 1].wall == WALL_NONE)
						{
							_tiles[i][j].obj = OBJ2_BLOCK1;
							_tiles[i][j].objFrameX = 0;
							_tiles[i][j].objFrameY = 2;
						}
						else if (_objtemp == 27)
						{
							_tiles[i][j].obj = OBJ2_BLOCK2;
							_tiles[i][j].objFrameX = 1;
							_tiles[i][j].objFrameY = 2;
						}
						else if (_objtemp == 23)
						{
							_tiles[i][j].obj = OBJ_BLOCK5;
							_tiles[i][j].objFrameX = 4;
							_tiles[i][j].objFrameY = 2;
						}
						else
						{
							_tiles[i][j].objFrameX = NULL;
							_tiles[i][j].objFrameY = NULL;
							_tiles[i][j].obj = OBJ_NONE;
						}
					}
					else
					{
						_tiles[i][j].objFrameX = NULL;
						_tiles[i][j].objFrameY = NULL;
						_tiles[i][j].obj = OBJ_NONE;
					}
				}


			}
			//stage3
			else if (_rnd == 2)
			{
			_objtemp = RND->getInt(100);
			_tiles[_xtemp][_ytemp].terrain = T3R_C;
			_tiles[_xtemp][_ytemp].terrainFrameX = 2;
			_tiles[_xtemp][_ytemp].terrainFrameY = 4;

			_tiles[_x2temp][_y2temp].terrain = T3R_C2;
			_tiles[_x2temp][_y2temp].terrainFrameX = 3;
			_tiles[_x2temp][_y2temp].terrainFrameY = 4;
			_tiles[_x2temp + 10][_y2temp + 10].terrain = T3R_C2;
			_tiles[_x2temp + 10][_y2temp + 10].terrainFrameX = 3;
			_tiles[_x2temp + 10][_y2temp + 10].terrainFrameY = 4;
			_tiles[_x2temp + 15][_y2temp + 15].terrain = T3R_C2;
			_tiles[_x2temp + 15][_y2temp + 15].terrainFrameX = 3;
			_tiles[_x2temp + 15][_y2temp + 15].terrainFrameY = 4;

			if (_tiles[i][j].wall == WALL_NONE)
			{

				_walltemp = RND->getInt(40);

				if (_walltemp < 5)
				{
					if (_tiles[i - 1][j].wall != WALL_NONE)
					{
						_tiles[i - 1][j].wallFrameX = NULL;
						_tiles[i - 1][j].wallFrameY = NULL;
						_tiles[i - 1][j].wall = WALL_NONE;

						_tiles[i - 1][j].terrain = T3R_C;
						_tiles[i - 1][j].terrainFrameX = 2;
						_tiles[i - 1][j].terrainFrameY = 4;
					}
					if (_tiles[i + 1][j].wall != WALL_NONE)
					{
						_tiles[i + 1][j].wallFrameX = NULL;
						_tiles[i + 1][j].wallFrameY = NULL;
						_tiles[i + 1][j].wall = WALL_NONE;

						_tiles[i + 1][j].terrain = T3R_C;
						_tiles[i + 1][j].terrainFrameX = 2;
						_tiles[i + 1][j].terrainFrameY = 4;
					}
					if (_tiles[i][j - 1].wall != WALL_NONE)
					{
						_tiles[i][j - 1].wallFrameX = NULL;
						_tiles[i][j - 1].wallFrameY = NULL;
						_tiles[i][j - 1].wall = WALL_NONE;

						_tiles[i][j - 1].terrain = T3R_C;
						_tiles[i][j - 1].terrainFrameX = 2;
						_tiles[i][j - 1].terrainFrameY = 4;
					}
					if (_tiles[i][j + 1].wall != WALL_NONE)
					{
						_tiles[i][j + 1].wallFrameX = NULL;
						_tiles[i][j + 1].wallFrameY = NULL;
						_tiles[i][j + 1].wall = WALL_NONE;

						_tiles[i][j + 1].terrain = T3R_C;
						_tiles[i][j + 1].terrainFrameX = 2;
						_tiles[i][j + 1].terrainFrameY = 4;
					}
				}
				else if (_walltemp < 11)
				{
					if (_tiles[i - 1][j].wall != WALL_NONE)
					{
						_tiles[i - 1][j].wallFrameX = NULL;
						_tiles[i - 1][j].wallFrameY = NULL;
						_tiles[i - 1][j].wall = WALL_NONE;

						_tiles[i - 1][j].terrain = T3R_C;
						_tiles[i - 1][j].terrainFrameX = 2;
						_tiles[i - 1][j].terrainFrameY = 4;
					}
					if (_tiles[i + 1][j].wall != WALL_NONE)
					{
						_tiles[i + 1][j].wallFrameX = NULL;
						_tiles[i + 1][j].wallFrameY = NULL;
						_tiles[i + 1][j].wall = WALL_NONE;

						_tiles[i + 1][j].terrain = T3R_C;
						_tiles[i + 1][j].terrainFrameX = 2;
						_tiles[i + 1][j].terrainFrameY = 4;
					}
				}
				else if (_walltemp < 17)
				{
					if (_tiles[i][j - 1].wall != WALL_NONE)
					{
						_tiles[i][j - 1].wallFrameX = NULL;
						_tiles[i][j - 1].wallFrameY = NULL;
						_tiles[i][j - 1].wall = WALL_NONE;

						_tiles[i][j - 1].terrain = T3R_C;
						_tiles[i][j - 1].terrainFrameX = 2;
						_tiles[i][j - 1].terrainFrameY = 4;
					}
					if (_tiles[i][j + 1].wall != WALL_NONE)
					{
						_tiles[i][j + 1].wallFrameX = NULL;
						_tiles[i][j + 1].wallFrameY = NULL;
						_tiles[i][j + 1].wall = WALL_NONE;

						_tiles[i][j + 1].terrain = T3R_C;
						_tiles[i][j + 1].terrainFrameX = 2;
						_tiles[i][j + 1].terrainFrameY = 4;
					}
				}
				else if (_walltemp < 23)
				{
					if (_tiles[i - 1][j].wall != WALL_NONE)
					{
						_tiles[i - 1][j].wallFrameX = NULL;
						_tiles[i - 1][j].wallFrameY = NULL;
						_tiles[i - 1][j].wall = WALL_NONE;

						_tiles[i - 1][j].terrain = T3R_C;
						_tiles[i - 1][j].terrainFrameX = 2;
						_tiles[i - 1][j].terrainFrameY = 4;
					}
					if (_tiles[i][j + 1].wall != WALL_NONE)
					{
						_tiles[i][j + 1].wallFrameX = NULL;
						_tiles[i][j + 1].wallFrameY = NULL;
						_tiles[i][j + 1].wall = WALL_NONE;

						_tiles[i][j + 1].terrain = T3R_C;
						_tiles[i][j + 1].terrainFrameX = 2;
						_tiles[i][j + 1].terrainFrameY = 4;
					}

				}
				else if (_walltemp < 31)
				{
					if (_tiles[i + 1][j].wall != WALL_NONE)
					{
						_tiles[i + 1][j].wallFrameX = NULL;
						_tiles[i + 1][j].wallFrameY = NULL;
						_tiles[i + 1][j].wall = WALL_NONE;

						_tiles[i + 1][j].terrain = T3R_C;
						_tiles[i + 1][j].terrainFrameX = 2;
						_tiles[i + 1][j].terrainFrameY = 4;
					}
					if (_tiles[i][j - 1].wall != WALL_NONE)
					{
						_tiles[i][j - 1].wallFrameX = NULL;
						_tiles[i][j - 1].wallFrameY = NULL;
						_tiles[i][j - 1].wall = WALL_NONE;

						_tiles[i][j - 1].terrain = T3R_C;
						_tiles[i][j - 1].terrainFrameX = 2;
						_tiles[i][j - 1].terrainFrameY = 4;
					}
				}
				else if (_walltemp < 40)
				{
					if (_tiles[i + 1][j].wall != WALL_NONE)
					{
						_tiles[i + 1][j].wallFrameX = NULL;
						_tiles[i + 1][j].wallFrameY = NULL;
						_tiles[i + 1][j].wall = WALL_NONE;

						_tiles[i + 1][j].terrain = T3R_C;
						_tiles[i + 1][j].terrainFrameX = 2;
						_tiles[i + 1][j].terrainFrameY = 4;
					}
					if (_tiles[i][j + 1].wall != WALL_NONE)
					{
						_tiles[i][j + 1].wallFrameX = NULL;
						_tiles[i][j + 1].wallFrameY = NULL;
						_tiles[i][j + 1].wall = WALL_NONE;

						_tiles[i][j + 1].terrain = T3R_C;
						_tiles[i][j + 1].terrainFrameX = 2;
						_tiles[i][j + 1].terrainFrameY = 4;
					}
				}
			}
			//OBJ
			if (_objtemp < 30)
			{
				if (_tiles[i][j].wall == WALL_NONE)
				{
					if (_objtemp == 26)
					{
						_tiles[i][j].obj = OBJ3_BLOCK1;
						_tiles[i][j].objFrameX = 0;
						_tiles[i][j].objFrameY = 3;
					}
					else if (_objtemp == 27)
					{
						_tiles[i][j].obj = OBJ3_BLOCK3;
						_tiles[i][j].objFrameX = 2;
						_tiles[i][j].objFrameY = 3;
					}
					else
					{
						_tiles[i][j].objFrameX = NULL;
						_tiles[i][j].objFrameY = NULL;
						_tiles[i][j].obj = OBJ_NONE;
					}
				}
				else if (_tiles[i][j].wall != WALL_NONE)
				{
					if (_objtemp < 3 && _tiles[i][j].wall != W3_2BT && _tiles[i][j].wall != W3_3B && _tiles[i][j].wall != W3_3L &&
						_tiles[i][j].wall != W3_3R && _tiles[i][j].wall != W3_B && _tiles[i][j].wall != W3_LB && _tiles[i][j].wall != W3_RB && _tiles[i][j].wall != W3_4)
					{
						_tiles[i][j].obj = OBJ2_BLOCK6;
						_tiles[i][j].objFrameX = 5;
						_tiles[i][j].objFrameY = 2;
					}
					else
					{
						_tiles[i][j].objFrameX = NULL;
						_tiles[i][j].objFrameY = NULL;
						_tiles[i][j].obj = OBJ_NONE;
					}
				}
			}


			}
		}
	}


	//2타일
	for (int i = 3; i < TILEX - 3; ++i) {
		for (int j = 3; j < TILEY - 3; ++j) {

			_tiletemp = RND->getInt(30);

			if (_rnd == 0)
			{
				if (_tiles[i][j].terrain == TR2_C)
				{

					if (_tiles[i - 1][j].wall == WALL_NONE && i > 5 && _tiletemp < 15)
					{
						_tiles[i - 1][j].terrain = TR2_C;
						_tiles[i - 1][j].terrainFrameX = 2;
						_tiles[i - 1][j].terrainFrameY = 0;
					}
					else if (_tiles[i + 1][j].wall == WALL_NONE && i < 25)
					{
						_tiles[i + 1][j].terrain = TR2_C;
						_tiles[i + 1][j].terrainFrameX = 2;
						_tiles[i + 1][j].terrainFrameY = 0;
					}
					if (_tiles[i][j - 1].wall == WALL_NONE && j > 5 && _tiletemp < 15)
					{
						_tiles[i][j - 1].terrain = TR2_C;
						_tiles[i][j - 1].terrainFrameX = 2;
						_tiles[i][j - 1].terrainFrameY = 0;
					}
					else if (_tiles[i][j + 1].wall == WALL_NONE && j < 25)
					{
						_tiles[i][j + 1].terrain = TR2_C;
						_tiles[i][j + 1].terrainFrameX = 2;
						_tiles[i][j + 1].terrainFrameY = 0;
					}

					if (_tiles[i - 1][j - 1].wall == WALL_NONE && _tiletemp < 8)
					{
						_tiles[i - 1][j - 1].terrain = TR2_C;
						_tiles[i - 1][j - 1].terrainFrameX = 2;
						_tiles[i - 1][j - 1].terrainFrameY = 0;
					}
					else if (_tiles[i + 1][j - 1].wall == WALL_NONE && _tiletemp < 15)
					{
						_tiles[i + 1][j - 1].terrain = TR2_C;
						_tiles[i + 1][j - 1].terrainFrameX = 2;
						_tiles[i + 1][j - 1].terrainFrameY = 0;
					}
					else if (_tiles[i + 1][j + 1].wall == WALL_NONE && _tiletemp < 22)
					{
						_tiles[i + 1][j + 1].terrain = TR2_C;
						_tiles[i + 1][j + 1].terrainFrameX = 2;
						_tiles[i + 1][j + 1].terrainFrameY = 0;
					}
					else if (_tiles[i - 1][j + 1].wall == WALL_NONE && _tiletemp < 30)
					{
						_tiles[i - 1][j + 1].terrain = TR2_C;
						_tiles[i - 1][j + 1].terrainFrameX = 2;
						_tiles[i - 1][j + 1].terrainFrameY = 0;
					}

				}
			}
			else if (_rnd == 2)
			{
				if (_tiles[i][j].terrain == T3R_C2)
				{

					if (_tiles[i - 1][j].wall == WALL_NONE && i > 5 && _tiletemp < 15)
					{
						_tiles[i - 1][j].terrain = T3R_C2;
						_tiles[i - 1][j].terrainFrameX = 3;
						_tiles[i - 1][j].terrainFrameY = 4;
					}
					else if (_tiles[i + 1][j].wall == WALL_NONE && i < 25)
					{
						_tiles[i + 1][j].terrain = T3R_C2;
						_tiles[i + 1][j].terrainFrameX = 3;
						_tiles[i + 1][j].terrainFrameY = 4;
					}

					if (_tiles[i][j - 1].wall == WALL_NONE && j > 5 && _tiletemp < 15)
					{
						_tiles[i][j - 1].terrain = T3R_C2;
						_tiles[i][j - 1].terrainFrameX = 3;
						_tiles[i][j - 1].terrainFrameY = 4;
					}
					else if (_tiles[i][j + 1].wall == WALL_NONE && j < 25)
					{
						_tiles[i][j + 1].terrain = T3R_C2;
						_tiles[i][j + 1].terrainFrameX = 3;
						_tiles[i][j + 1].terrainFrameY = 4;
					}

					if (_tiles[i - 1][j - 1].wall == WALL_NONE && _tiletemp < 8)
					{
						_tiles[i - 1][j - 1].terrain = T3R_C2;
						_tiles[i - 1][j - 1].terrainFrameX = 3;
						_tiles[i - 1][j - 1].terrainFrameY = 4;
					}
					else if (_tiles[i + 1][j - 1].wall == WALL_NONE && _tiletemp < 15)
					{
						_tiles[i + 1][j - 1].terrain = T3R_C2;
						_tiles[i + 1][j - 1].terrainFrameX = 3;
						_tiles[i + 1][j - 1].terrainFrameY = 4;
					}
					else if (_tiles[i + 1][j + 1].wall == WALL_NONE && _tiletemp < 22)
					{
						_tiles[i + 1][j + 1].terrain = T3R_C2;
						_tiles[i + 1][j + 1].terrainFrameX = 3;
						_tiles[i + 1][j + 1].terrainFrameY = 4;
					}
					else if (_tiles[i - 1][j + 1].wall == WALL_NONE && _tiletemp < 30)
					{
						_tiles[i - 1][j + 1].terrain = T3R_C2;
						_tiles[i - 1][j + 1].terrainFrameX = 3;
						_tiles[i - 1][j + 1].terrainFrameY = 4;
					}

				}
			}
		}
	}

	//플레이어초기 위치
	_walltemp = RND->getInt(4);

	if (_walltemp == 0 || _walltemp == 1) // 좌상 탐색
	{
		_x2temp = RND->getInt(3);
		_y2temp = RND->getInt(3);

		while (_tiles[_x2temp][_y2temp].wall != WALL_NONE || _tiles[_x2temp][_y2temp].obj != OBJ_NONE)
		{
			_x2temp++;
			_y2temp++;
		}

		if (PLAYERMANAGER->getPlayerType() == NULL)
		{
			PLAYERMANAGER->setplayer(FISH, _tiles[_x2temp][_y2temp].rc.right - 64, _tiles[_x2temp][_y2temp].rc.top);
		}
		else
		{
			PLAYERMANAGER->setPlayerPosition(PointMake(_tiles[_x2temp][_y2temp].rc.right - 64, _tiles[_x2temp][_y2temp].rc.top));
			//PLAYERMANAGER->setplayer(PLAYERMANAGER->getPlayerType(), _tiles[_x2temp][_y2temp].rc.right - 64, _tiles[_x2temp][_y2temp].rc.top);
		}

	}
	else if (_walltemp == 2 || _walltemp == 3)// 우하 탐색
	{
		_x2temp = 27 + RND->getInt(2);
		_y2temp = 26 + RND->getInt(3);

		while (_tiles[_x2temp][_y2temp].wall != WALL_NONE || _tiles[_x2temp][_y2temp].obj != OBJ_NONE)
		{
			_x2temp--;
			_y2temp--;
		}

		if (PLAYERMANAGER->getPlayerType() == NULL)
		{
			PLAYERMANAGER->setplayer(FISH, _tiles[_x2temp][_y2temp].rc.right - 64, _tiles[_x2temp][_y2temp].rc.top);
		}
		else
		{
			PLAYERMANAGER->setPlayerPosition(PointMake(_tiles[_x2temp][_y2temp].rc.right - 64, _tiles[_x2temp][_y2temp].rc.top));
			//PLAYERMANAGER->setplayer(PLAYERMANAGER->getPlayerType(), _tiles[_x2temp][_y2temp].rc.right - 64, _tiles[_x2temp][_y2temp].rc.top);
		}
	}
	

	//에너미
	for (int i = 3; i < TILEX - 3; i++)
		for (int j = 3; j < TILEY - 3; j++)
		{
			if (_walltemp <= 1)
			{
				if (i < 10 && j < 10) continue;
			}
			else if (_walltemp <= 3)
			{
				if (i > 20 && j > 20) continue;
			}
			_tiletemp = RND->getInt(100);
			_enemytemp = RND->getInt(100);

			if (_tiles[i][j].wall == WALL_NONE && _tiles[i][j].obj == OBJ_NONE && _tiletemp < 8)
			{
				if (_rnd == 0)
				{
					if (_enemytemp > 60)
					{
						ENEMYMANAGER->addEnemys("custom", BANDIT, _tiles[i][j].rc.right - 64, _tiles[i][j].rc.top);
					}
					else if (_enemytemp > 40)
					{
						ENEMYMANAGER->addEnemys("custom", BIGMAGGOT, _tiles[i][j].rc.right - 64, _tiles[i][j].rc.top);
					}
					else if (_enemytemp > 20)
					{
						ENEMYMANAGER->addEnemys("custom", SCOLPION, _tiles[i][j].rc.right - 64, _tiles[i][j].rc.top);
					}
					else if (_enemytemp > 0)
					{
						ENEMYMANAGER->addEnemys("custom", MAGGOTNEST, _tiles[i][j].rc.right - 64, _tiles[i][j].rc.top);
					}
				}
				else if (_rnd == 1)
				{
					if (_enemytemp > 60)
					{
						ENEMYMANAGER->addEnemys("custom", RAT, _tiles[i][j].rc.right - 64, _tiles[i][j].rc.top);
					}
					else if (_enemytemp > 40)
					{
						ENEMYMANAGER->addEnemys("custom", BIGRAT, _tiles[i][j].rc.right - 64, _tiles[i][j].rc.top);
					}
					else if (_enemytemp > 20)
					{
						ENEMYMANAGER->addEnemys("custom", GREENRAT, _tiles[i][j].rc.right - 64, _tiles[i][j].rc.top);
					}
					else if (_enemytemp > 10)
					{
						ENEMYMANAGER->addEnemys("custom", GREENFROG, _tiles[i][j].rc.right - 64, _tiles[i][j].rc.top);
					}
					else if (_enemytemp > 0)
					{
						ENEMYMANAGER->addEnemys("custom", GATOR, _tiles[i][j].rc.right - 64, _tiles[i][j].rc.top);
					}
				}
				else if (_rnd == 2)
				{
					if (_enemytemp > 60)
					{
						ENEMYMANAGER->addEnemys("custom", RAVEN, _tiles[i][j].rc.right - 64, _tiles[i][j].rc.top);
					}
					else if (_enemytemp > 20)
					{
						ENEMYMANAGER->addEnemys("custom", SNIPER, _tiles[i][j].rc.right - 64, _tiles[i][j].rc.top);
					}
					else if (_enemytemp > 10)
					{
						ENEMYMANAGER->addEnemys("custom", SALAMADER, _tiles[i][j].rc.right - 64, _tiles[i][j].rc.top);
					}
					else if (_enemytemp > 0)
					{
						ENEMYMANAGER->addEnemys("custom", ASSASSIN, _tiles[i][j].rc.right - 64, _tiles[i][j].rc.top);
					}
				}
			}
			else
			{

			}


		}


	//보스
	_x2temp = 10 + RND->getInt(10);
	_y2temp = 10 + RND->getInt(10);

	
	while (_tiles[_x2temp][_y2temp].wall != WALL_NONE || _tiles[_x2temp][_y2temp].obj != OBJ_NONE)
	{
		_x2temp = 10 + RND->getInt(10);
		_y2temp = 10 + RND->getInt(10);
	}

	if (_rnd == 0)
	{
		if (stage_first == 0 && stage_second == 1) // 빅밴딧
		{
			ENEMYMANAGER->addEnemys("custom", BIGBANDIT, _tiles[_x2temp][_y2temp].rc.right - 64, _tiles[_x2temp][_y2temp].rc.top);

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++)
				{
					_tiles[_x2temp - 1 + i][_y2temp - 1 + j].objFrameX = NULL;
					_tiles[_x2temp - 1 + i][_y2temp - 1 + j].objFrameY = NULL;
					_tiles[_x2temp - 1 + i][_y2temp - 1 + j].wallFrameX = NULL;
					_tiles[_x2temp - 1 + i][_y2temp - 1 + j].wallFrameY = NULL;
					_tiles[_x2temp - 1 + i][_y2temp - 1 + j].obj = OBJ_NONE;
					_tiles[_x2temp - 1 + i][_y2temp - 1 + j].wall = WALL_NONE;
				}
			}
		}
	}
	else if (_rnd == 2)
	{
		if (stage_first == 2 && stage_second == 1) //빅독
		{
			ENEMYMANAGER->addEnemys("custom", BIGDOG, _tiles[_x2temp][_y2temp].rc.right - 128, _tiles[_x2temp][_y2temp].rc.top);

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++)
				{
					_tiles[_x2temp - 1 + i][_y2temp - 1 + j].objFrameX = NULL;
					_tiles[_x2temp - 1 + i][_y2temp - 1 + j].objFrameY = NULL;
					_tiles[_x2temp - 1 + i][_y2temp - 1 + j].wallFrameX = NULL;
					_tiles[_x2temp - 1 + i][_y2temp - 1 + j].wallFrameY = NULL;
					_tiles[_x2temp - 1 + i][_y2temp - 1 + j].obj = OBJ_NONE;
					_tiles[_x2temp - 1 + i][_y2temp - 1 + j].wall = WALL_NONE;
				}
			}
		}

	}

	//아이템 박스 추가
	_x2temp = RND->getInt(15) + 5;
	_y2temp = RND->getInt(15) + 5;

	while (_tiles[_x2temp][_y2temp].wall != WALL_NONE || _tiles[_x2temp][_y2temp].obj != OBJ_NONE)
	{
		_x2temp = RND->getInt(10) + 5;
		_y2temp = RND->getInt(10) + 5;
	}

	ITEMMANAGER->setItembox(BULLETITEMBOX, _tiles[_x2temp][_y2temp].rc.right - 32, _tiles[_x2temp][_y2temp].rc.top+32);


	_x2temp = RND->getInt(15) + 5;
	_y2temp = RND->getInt(15) + 5;

	while (_tiles[_x2temp][_y2temp].wall != WALL_NONE || _tiles[_x2temp][_y2temp].obj != OBJ_NONE)
	{
		_x2temp = RND->getInt(15) + 5;
		_y2temp = RND->getInt(15) + 5;
	}

	ITEMMANAGER->setItembox(WEAPOMITEMBOX, _tiles[_x2temp][_y2temp].rc.right - 32, _tiles[_x2temp][_y2temp].rc.top+32);



	_x2temp = RND->getInt(15) + 5;
	_y2temp = RND->getInt(15) + 5;

	while (_tiles[_x2temp][_y2temp].wall != WALL_NONE || _tiles[_x2temp][_y2temp].obj != OBJ_NONE)
	{
		_x2temp = RND->getInt(20) + 5;
		_y2temp = RND->getInt(20) + 5;
	}

	ITEMMANAGER->setItembox(MEDKITITEMBOX, _tiles[_x2temp][_y2temp].rc.right - 32, _tiles[_x2temp][_y2temp].rc.top+32);

	_rnd = 3;
}

void mapManager::setImage()
{
	IMAGEMANAGER->addFrameImage("mapTiles", "image/Scene/maptool/maptool-tile2.bmp", 0, 0, 384, 448, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mapWall", "image/Scene/maptool/maptool-wall2.bmp", 0, 0, 384, 448, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mapObj", "image/Scene/maptool/obj-test.bmp", 0, 0, 384,448, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("samTiles", "image/Scene/maptool/tile-test.bmp", 0, 0, 384, 448, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("samWall", "image/Scene/maptool/wall-test.bmp", 0, 0, 384, 448, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("playerset","image/Scene/maptool/player_tile.bmp", 0, 0, 384, 64, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemyset","image/Scene/maptool/enemy_tile.bmp",0,0,384,192,6,3,true, RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("bossset", "image/Scene/maptool/boss_tile.bmp", 0, 0, 384, 129, 2, 1, true, RGB(255, 0, 255));
}

void mapManager::setTiles()
{
	//타일 struct의 init
	for (int i = 0; i < TILEX; ++i)
		for (int j = 0; j < TILEY; ++j)
		{
			_tiles[i][j].terrainFrameX = 0;
			_tiles[i][j].terrainFrameY = 0;
			_tiles[i][j].objFrameX = 0;
			_tiles[i][j].objFrameY = 0;
			_tiles[i][j].objFrameX = 0;
			_tiles[i][j].objFrameY = 0;
			_tiles[i][j].terrain = terrainSelect(_tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
			_tiles[i][j].obj = OBJ_NONE;
			_tiles[i][j].wall = WALL_NONE;
		}
}

void mapManager::setSampleTile()
{
	_Select = DrawTerrain;

	//sampleTile의 위치를 지정해 준다.
	for (int i = 0; i < SAMPLETILEX; ++i)
		for (int j = 0; j < SAMPLETILEY; ++j) {
			_sampleTile[i][j].terrainFrameX = i;
			_sampleTile[i][j].terrainFrameY = j;

			//RectMake, RectMakeCenter
			SetRect(&_sampleTile[i][j].rcTile,
				(WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth()) + i * TILESIZE - 60,
				j * TILESIZE + 50,
				(WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth()) + i * TILESIZE + TILESIZE - 60,
				j * TILESIZE + TILESIZE + 50);
		}
}

void mapManager::setMap()
{
	//샘플에서 찍은거 저장
	for (int i = 0; i < SAMPLETILEX; ++i)
	{
		for (int j = 0; j < SAMPLETILEY; ++j)
		{
			if (PtInRect(&_sampleTile[i][j].rcTile, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_Select == DrawTerrain)
				{
					if (i == 0 && j == 0)
					{
						_currentTile.x = _sampleTile[0][0].terrainFrameX;
						_currentTile.y = _sampleTile[0][0].terrainFrameY;
					}
					else if (i == 2 && j == 0)
					{
						_currentTile.x = _sampleTile[1][0].terrainFrameX;
						_currentTile.y = _sampleTile[1][0].terrainFrameY;
					}
					else if (i == 4 && j == 0)
					{
						_currentTile.x = _sampleTile[2][0].terrainFrameX;
						_currentTile.y = _sampleTile[2][0].terrainFrameY;
					}

					else if (i == 0 && j == 2)
					{
						_currentTile.x = _sampleTile[0][2].terrainFrameX;
						_currentTile.y = _sampleTile[0][2].terrainFrameY;
					}
					else if (i == 1 && j == 2)
					{
						_currentTile.x = _sampleTile[1][2].terrainFrameX;
						_currentTile.y = _sampleTile[1][2].terrainFrameY;
					}
					else if (i == 2 && j == 2)
					{
						_currentTile.x = _sampleTile[2][2].terrainFrameX;
						_currentTile.y = _sampleTile[2][2].terrainFrameY;
					}
					else if (i == 3 && j == 2)
					{
						_currentTile.x = _sampleTile[0][3].terrainFrameX;
						_currentTile.y = _sampleTile[0][3].terrainFrameY;
					}
					else if (i == 4 && j == 2)
					{
						_currentTile.x = _sampleTile[2][3].terrainFrameX;
						_currentTile.y = _sampleTile[2][3].terrainFrameY;
					}
					else if (i == 5 && j == 2)
					{
						_currentTile.x = _sampleTile[3][3].terrainFrameX;
						_currentTile.y = _sampleTile[3][3].terrainFrameY;
					}

					else if (i == 0 && j == 4)
					{
						_currentTile.x = _sampleTile[2][4].terrainFrameX;
						_currentTile.y = _sampleTile[2][4].terrainFrameY;
					}
					else if (i == 2 && j == 4)
					{
						_currentTile.x = _sampleTile[3][4].terrainFrameX;
						_currentTile.y = _sampleTile[3][4].terrainFrameY;
					}

				}
				else if (_Select == DrawWall)
				{
					if (i == 0 && j == 0)
					{
						_currentTile.x = _sampleTile[1][1].terrainFrameX;
						_currentTile.y = _sampleTile[1][1].terrainFrameY;
					}
					else if (i == 0 && j == 2)
					{
						_currentTile.x = _sampleTile[3][3].terrainFrameX;
						_currentTile.y = _sampleTile[3][3].terrainFrameY;
					}
					else if (i == 2 && j == 2)
					{
						_currentTile.x = _sampleTile[4][3].terrainFrameX;
						_currentTile.y = _sampleTile[4][3].terrainFrameY;
					}
					else if (i == 4 && j == 2)
					{
						_currentTile.x = _sampleTile[5][3].terrainFrameX;
						_currentTile.y = _sampleTile[5][3].terrainFrameY;
					}
					else if (i == 0 && j == 4)
					{
						_currentTile.x = _sampleTile[2][5].terrainFrameX;
						_currentTile.y = _sampleTile[2][5].terrainFrameY;
					}
					else if (i == 2 && j == 4)
					{
						_currentTile.x = _sampleTile[3][5].terrainFrameX;
						_currentTile.y = _sampleTile[3][5].terrainFrameY;
					}
				}
				else if (_Select == DrawObj)
				{
					_currentTile.x = _sampleTile[i][j].terrainFrameX;
					_currentTile.y = _sampleTile[i][j].terrainFrameY;
				}
				else
				{
					_currentTile.x = _sampleTile[i][j].terrainFrameX;
					_currentTile.y = _sampleTile[i][j].terrainFrameY;
				}

				break;
			}
		}
	}

	

	//맵에 찍는거
	for (int i = 0; i < width_count; ++i) {
		for (int j = 0; j < height_count; ++j)
		{
			//showTile에 PtInRect & 클릭 시 = 맵에 찍음
			if (PtInRect(&_showTile[i][j].rc, _ptMouse)) {

				if (_Select == DrawPlayer) {
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
						//선택한 FrameX번째의 PLAYERTYPE 으로 player set
						PLAYERMANAGER->setplayer((PLAYERTYPE)_currentTile.x, _showTile[i][j].pt.x * 64, _showTile[i][j].pt.y * 64);
					}
				}
				else if (_Select == DrawEnemy) {
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
						//선택한 FrameX번째의 enemy으로 enemy set
						//EnemyManager create
						ENEMYMANAGER->addEnemys("custom", (ENEMYTYPE)getEnemyType(_currentTile.x,_currentTile.y), _showTile[i][j].pt.x * 64, _showTile[i][j].pt.y * 64);
						
					}
				}
				else if (_Select == DrawBoss) {
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
						ENEMYMANAGER->addEnemys("custom", (ENEMYTYPE)getEnemyType(_currentTile.x, _currentTile.y), _showTile[i][j].pt.x * 64, _showTile[i][j].pt.y * 64);
						
					}
				}
				else {
					//누른 곳
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
						_min = _showTile[i][j].pt;

					}
					//뗀 곳
					if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
						_max = _showTile[i][j].pt;

						if (_min.x > _max.x) {
							int temp;
							temp = _min.x;
							_min.x = _max.x;
							_max.x = temp;
						}
						if (_min.y > _max.y) {
							int temp;
							temp = _min.y;
							_min.y = _max.y;
							_max.y = temp;
						}
						if (_max.x < _min.x) {
							int temp;
							temp = _max.x;
							_max.x = _min.x;
							_min.x = temp;
						}
						if (_max.y < _min.y) {
							int temp;
							temp = _max.x;
							_max.x = _min.x;
							_min.x = temp;
						}

						for (int i = _min.x; i <= _max.x; ++i) {
							for (int j = _min.y; j <= _max.y; ++j) {
								if (_Select == DrawTerrain)
								{
									_tiles[i][j].terrainFrameX = _currentTile.x;
									_tiles[i][j].terrainFrameY = _currentTile.y;

									_tiles[i][j].terrain = terrainSelect(_currentTile.x, _currentTile.y);
								}
								else if (_Select == DrawObj)
								{
									_tiles[i][j].objFrameX = _currentTile.x;
									_tiles[i][j].objFrameY = _currentTile.y;

									_tiles[i][j].obj = objSelect(_currentTile.x, _currentTile.y);
								}
								else if (_Select == DrawWall)
								{
									_tiles[i][j].wallFrameX = _currentTile.x;
									_tiles[i][j].wallFrameY = _currentTile.y;

									_tiles[i][j].wall = wallSelect(_currentTile.x, _currentTile.y);
								}
								else if (_Select == Eraser)
								{
									//i*j 번째 해당하는 위치에 있는 에너미들을 없앤다.
									ENEMYMANAGER->deleteEnemys("custom",i*TILESIZE,j*TILESIZE);

									_tiles[i][j].objFrameX = NULL;
									_tiles[i][j].objFrameY = NULL;
									_tiles[i][j].wallFrameX = NULL;
									_tiles[i][j].wallFrameY = NULL;
									_tiles[i][j].obj = OBJ_NONE;
									_tiles[i][j].wall = WALL_NONE;
								}

								InvalidateRect(_hWnd, NULL, false);
							}
						}
					}
				}
			}
		}
	}
}
void mapManager::moveIndex()
{//moveCamera
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		_pt.x--;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		_pt.x++;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		_pt.y--;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		_pt.y++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SCROLL)) {
		width_count++;
		height_count++;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SCROLL)) {
		width_count--;
		height_count--;
	}
	//예외처리
	if (_pt.x <= 0) {
		_pt.x = 0;
	}
	if (_pt.x >= TILEX - SHOW_TILEX) {
		_pt.x = TILEX - SHOW_TILEX;
	}
	if (_pt.y <= 0) {
		_pt.y = 0;
	}
	if (_pt.y >= TILEY - SHOW_TILEY) {
		_pt.y = TILEY - SHOW_TILEY;
	}

	//index에 따른 tile RECT 설정
	MAPMANAGER->updateTileIndex();
}

void mapManager::updateTileIndex()
{
	int current_width = 768 / width_count;
	int current_height = 648 / height_count;
	//index변경
	for (int i = 0; i < width_count; ++i) {
		for (int j = 0; j < height_count; ++j) {
			_showTile[i][j].pt.x = _pt.x + i;
			_showTile[i][j].pt.y = _pt.y + j;
			_showTile[i][j].rc = RectMake(i * current_width, j * current_height, current_width, current_height);
		}
	}
}

void mapManager::autoTile()
{
	for (int i = 1; i < TILEX - 1; ++i) {
		for (int j = 1; j < TILEY - 1; ++j)
		{
			// 1탄 테두리
			if (_tiles[i][j].terrain == TR2_C || _tiles[i][j].terrain == TR2_C1 || _tiles[i][j].terrain == TR2_C2)
			{
				if (_tiles[i - 1][j].terrain == TR_C) {
					_tiles[i - 1][j].terrain = TR3_4;
					_tiles[i - 1][j].terrainFrameX = 3;
					_tiles[i - 1][j].terrainFrameY = 1;
				}
				if (_tiles[i + 1][j].terrain == TR_C) {
					_tiles[i + 1][j].terrain = TR3_3;
					_tiles[i + 1][j].terrainFrameX = 2;
					_tiles[i + 1][j].terrainFrameY = 1;
				}
				if (_tiles[i][j - 1].terrain == TR_C) {
					_tiles[i][j - 1].terrain = TR3_1;
					_tiles[i][j - 1].terrainFrameX = 0;
					_tiles[i][j - 1].terrainFrameY = 1;
				}
				if (_tiles[i][j + 1].terrain == TR_C) {
					_tiles[i][j + 1].terrain = TR3_2;
					_tiles[i][j + 1].terrainFrameX = 1;
					_tiles[i][j + 1].terrainFrameY = 1;
				}
			}



			if (_tiles[i][j].terrain == TR3_4)
			{
				if (_tiles[i + 1][j].terrain != TR2_C && _tiles[i + 1][j].terrain != TR2_C1 && _tiles[i + 1][j].terrain != TR2_C2)
				{
					_tiles[i][j].terrain = TR_C;
					_tiles[i][j].terrainFrameX = 0;
					_tiles[i][j].terrainFrameY = 0;
				}
			}

			if (_tiles[i][j].terrain == TR3_3)
			{
				if (_tiles[i - 1][j].terrain != TR2_C && _tiles[i - 1][j].terrain != TR2_C1 && _tiles[i - 1][j].terrain != TR2_C2)
				{
					_tiles[i][j].terrain = TR_C;
					_tiles[i][j].terrainFrameX = 0;
					_tiles[i][j].terrainFrameY = 0;
				}
			}

			if (_tiles[i][j].terrain == TR3_2)
			{
				if (_tiles[i][j - 1].terrain != TR2_C && _tiles[i][j - 1].terrain != TR2_C1 && _tiles[i][j - 1].terrain != TR2_C2)
				{
					_tiles[i][j].terrain = TR_C;
					_tiles[i][j].terrainFrameX = 0;
					_tiles[i][j].terrainFrameY = 0;
				}
			}

			if (_tiles[i][j].terrain == TR3_1)
			{
				if (_tiles[i][j + 1].terrain != TR2_C && _tiles[i][j + 1].terrain != TR2_C1 && _tiles[i][j + 1].terrain != TR2_C2)
				{
					_tiles[i][j].terrain = TR_C;
					_tiles[i][j].terrainFrameX = 0;
					_tiles[i][j].terrainFrameY = 0;
				}
			}



			//3탄 잔디 테두리
			if (_tiles[i][j].terrain == T3R_C2)
			{
				if (_tiles[i - 1][j].terrain == T3R_C) {
					_tiles[i - 1][j].terrain = T3R_C2R;
					_tiles[i - 1][j].terrainFrameX = 0;
					_tiles[i - 1][j].terrainFrameY = 5;
				}
				if (_tiles[i + 1][j].terrain == T3R_C) {
					_tiles[i + 1][j].terrain = T3R_C2L;
					_tiles[i + 1][j].terrainFrameX = 1;
					_tiles[i + 1][j].terrainFrameY = 5;
				}
				if (_tiles[i][j - 1].terrain == T3R_C) {
					_tiles[i][j - 1].terrain = T3R_C2T;
					_tiles[i][j - 1].terrainFrameX = 2;
					_tiles[i][j - 1].terrainFrameY = 5;
				}
				if (_tiles[i][j + 1].terrain == T3R_C) {
					_tiles[i][j + 1].terrain = T3R_C2B;
					_tiles[i][j + 1].terrainFrameX = 4;
					_tiles[i][j + 1].terrainFrameY = 4;
				}
			}


			if (_tiles[i][j].terrain == T3R_C2R)
			{
				if (_tiles[i + 1][j].terrain != T3R_C2)
				{
					_tiles[i][j].terrain = T3R_C;
					_tiles[i][j].terrainFrameX = 2;
					_tiles[i][j].terrainFrameY = 4;
				}
			}
			if (_tiles[i][j].terrain == T3R_C2L)
			{
				if (_tiles[i - 1][j].terrain != T3R_C2)
				{
					_tiles[i][j].terrain = T3R_C;
					_tiles[i][j].terrainFrameX = 2;
					_tiles[i][j].terrainFrameY = 4;
				}
			}
			if (_tiles[i][j].terrain == T3R_C2T)
			{
				if (_tiles[i][j + 1].terrain != T3R_C2)
				{
					_tiles[i][j].terrain = T3R_C;
					_tiles[i][j].terrainFrameX = 2;
					_tiles[i][j].terrainFrameY = 4;
				}
			}
			if (_tiles[i][j].terrain == T3R_C2B)
			{
				if (_tiles[i][j - 1].terrain != T3R_C2)
				{
					_tiles[i][j].terrain = T3R_C;
					_tiles[i][j].terrainFrameX = 2;
					_tiles[i][j].terrainFrameY = 4;
				}
			}


			//그림자
			if (j != TILEY - 1)
			{
				if (_tiles[i][j].wall == W_B || _tiles[i][j].wall == W_LB || _tiles[i][j].wall == W_RB || _tiles[i][j].wall == W_3L || _tiles[i][j].wall == W_3R || _tiles[i][j].wall == W_3B || _tiles[i][j].wall == W_4 || _tiles[i][j].wall == W_2BT)
				{
					_tiles[i][j + 1].obj = OBJ1_SHD;
					_tiles[i][j + 1].objFrameX = 0;
					_tiles[i][j + 1].objFrameY = 6;
				}

				if (_tiles[i][j].wall == W2_B || _tiles[i][j].wall == W2_B2 || _tiles[i][j].wall == W2_B1)
				{
					_tiles[i][j + 1].obj = OBJ2_SHD;
					_tiles[i][j + 1].objFrameX = 2;
					_tiles[i][j + 1].objFrameY = 6;
				}


				if (_tiles[i][j].wall == W3_B || _tiles[i][j].wall == W3_LB || _tiles[i][j].wall == W3_RB || _tiles[i][j].wall == W3_3L || _tiles[i][j].wall == W3_3R || _tiles[i][j].wall == W3_3B || _tiles[i][j].wall == W3_4 || _tiles[i][j].wall == W3_2BT)
				{
					_tiles[i][j + 1].obj = OBJ3_SHD;
					_tiles[i][j + 1].objFrameX = 4;
					_tiles[i][j + 1].objFrameY = 6;
				}


				if (_tiles[i][j].obj == OBJ1_SHD)
				{
					if (_tiles[i][j - 1].wall != W_B && _tiles[i][j - 1].wall != W_LB && _tiles[i][j - 1].wall != W_RB && _tiles[i][j - 1].wall != W_3L && _tiles[i][j - 1].wall != W_3R && _tiles[i][j - 1].wall != W_3B && _tiles[i][j - 1].wall != W_4 && _tiles[i][j - 1].wall != W_2BT)
					{
						_tiles[i][j].obj = OBJ_NONE;
					}
				}
				if (_tiles[i][j].obj == OBJ2_SHD)
				{
					if (_tiles[i][j - 1].wall != W2_B && _tiles[i][j - 1].wall != W2_B2 && _tiles[i][j - 1].wall != W2_B1)
					{
						_tiles[i][j].obj = OBJ_NONE;
					}
				}
				if (_tiles[i][j].obj == OBJ3_SHD)
				{
					if (_tiles[i][j - 1].wall != W3_B && _tiles[i][j - 1].wall != W3_LB && _tiles[i][j - 1].wall != W3_RB && _tiles[i][j - 1].wall != W3_3L && _tiles[i][j - 1].wall != W3_3R && _tiles[i][j - 1].wall != W3_3B && _tiles[i][j - 1].wall != W3_4 && _tiles[i][j - 1].wall != W3_2BT)
					{
						_tiles[i][j].obj = OBJ_NONE;
					}
				}
			}

			//obj 예외처리
			if (_tiles[i][j].wall != WALL_NONE)
			{
				if (_tiles[i][j].obj != OBJ_BLOCK1 && _tiles[i][j].obj != OBJ_BLOCK2 && _tiles[i][j].obj != OBJ2_BLOCK5)
				{
					_tiles[i][j].objFrameX = NULL;
					_tiles[i][j].objFrameY = NULL;
					_tiles[i][j].obj = OBJ_NONE;
				}
			}


			if ((_tiles[i][j].wall == W_4 || _tiles[i][j].wall == W_LB || _tiles[i][j].wall == W_RB || _tiles[i][j].wall == W_B || _tiles[i][j].wall == W_2BT ||
				_tiles[i][j].wall == W_3R || _tiles[i][j].wall == W_3B || _tiles[i][j].wall == W_3L) && (_tiles[i][j].obj == OBJ_BLOCK1 || _tiles[i][j].obj == OBJ_BLOCK2))
			{
				_tiles[i][j].objFrameX = NULL;
				_tiles[i][j].objFrameY = NULL;
				_tiles[i][j].obj = OBJ_NONE;
			}

			if (_tiles[i][j].wall == WALL_NONE && (_tiles[i][j].obj == OBJ_BLOCK1 || _tiles[i][j].obj == OBJ_BLOCK2 || _tiles[i][j].obj == OBJ2_BLOCK6))
			{
				_tiles[i][j].objFrameX = NULL;
				_tiles[i][j].objFrameY = NULL;
				_tiles[i][j].obj = OBJ_NONE;
			}



			if ((_tiles[i][j].wall == W_3R || _tiles[i][j].wall == W_3L || _tiles[i][j].wall == W_B || _tiles[i][j].wall == W_RB || _tiles[i][j].wall == W_LB || _tiles[i][j].wall == W_2BT) && (_tiles[i][j + 1].wall != WALL_NONE))
			{
				_tiles[i][j].wall = W_ROOF;
				_tiles[i][j].wallFrameX = 1;
				_tiles[i][j].wallFrameY = 1;
			}

			if (_tiles[i][j].wall == W_2RL && (_tiles[i + 1][j].wall != WALL_NONE || _tiles[i - 1][j].wall != WALL_NONE))
			{
				_tiles[i][j].wall = W_ROOF;
				_tiles[i][j].wallFrameX = 1;
				_tiles[i][j].wallFrameY = 1;
			}

			//타일 예외처리
			if (_tiles[i][j].terrain == TR3_1 || _tiles[i][j].terrain == TR3_2 || _tiles[i][j].terrain == TR3_3 || _tiles[i][j].terrain == TR3_4)
			{
				if ((_tiles[i - 1][j].terrain == TR2_C || _tiles[i - 1][j].wall != WALL_NONE)
					&& (_tiles[i + 1][j].terrain == TR2_C || _tiles[i + 1][j].wall != WALL_NONE)
					&& (_tiles[i][j - 1].terrain == TR2_C || _tiles[i][j - 1].wall != WALL_NONE)
					&& (_tiles[i][j + 1].terrain == TR2_C || _tiles[i][j + 1].wall != WALL_NONE))
				{
					_tiles[i][j].terrain = TR2_C;
					_tiles[i][j].terrainFrameX = 2;
					_tiles[i][j].terrainFrameY = 0;

				}
			}

			if (_tiles[i][j].terrain == T3R_C2B || _tiles[i][j].terrain == T3R_C2T || _tiles[i][j].terrain == T3R_C2R || _tiles[i][j].terrain == T3R_C2L)
			{
				if ((_tiles[i - 1][j].terrain == T3R_C2 || _tiles[i - 1][j].wall != WALL_NONE)
					&& (_tiles[i + 1][j].terrain == T3R_C2 || _tiles[i + 1][j].wall != WALL_NONE)
					&& (_tiles[i][j - 1].terrain == T3R_C2 || _tiles[i][j - 1].wall != WALL_NONE)
					&& (_tiles[i][j + 1].terrain == T3R_C2 || _tiles[i][j + 1].wall != WALL_NONE))
				{
					_tiles[i][j].terrain = T3R_C2;
					_tiles[i][j].terrainFrameX = 3;
					_tiles[i][j].terrainFrameY = 4;

				}
			}


			if (_tiles[i][j].terrain == TR2_C)
			{
				if (_tiles[i - 1][j].terrain != TR2_C && _tiles[i + 1][j].terrain != TR2_C && _tiles[i][j - 1].terrain != TR2_C && _tiles[i][j + 1].terrain != TR2_C)
				{
					_tiles[i][j].terrain = TR_C;
					_tiles[i][j].terrainFrameX = 0;
					_tiles[i][j].terrainFrameY = 0;
				}
			}

			if (_tiles[i][j].terrain == T3R_C2)
			{
				if (_tiles[i - 1][j].terrain != T3R_C2 && _tiles[i + 1][j].terrain != T3R_C2 && _tiles[i][j - 1].terrain != T3R_C2 && _tiles[i][j + 1].terrain != T3R_C2)
				{
					_tiles[i][j].terrain = T3R_C;
					_tiles[i][j].terrainFrameX = 2;
					_tiles[i][j].terrainFrameY = 4;
				}
			}

			//벽 예외처리


			if (_tiles[i][j].wall == W3_C2)
			{
				if (
					(_tiles[i - 1][j].wall == W3_L || _tiles[i - 1][j].wall == W3_LB || _tiles[i - 1][j].wall == W3_3L || _tiles[i - 1][j].wall == W3_B || _tiles[i - 1][j].wall == W3_LT || _tiles[i - 1][j].wall == W3_T || _tiles[i - 1][j].wall == W3_2BT) ||
					(_tiles[i + 1][j].wall == W3_R || _tiles[i + 1][j].wall == W3_RB || _tiles[i + 1][j].wall == W3_3R || _tiles[i + 1][j].wall == W3_B || _tiles[i + 1][j].wall == W3_RT || _tiles[i + 1][j].wall == W3_T || _tiles[i - 1][j].wall == W3_2BT) ||
					(_tiles[i][j - 1].wall == W3_T || _tiles[i][j - 1].wall == W3_RT || _tiles[i][j - 1].wall == W3_LT || _tiles[i][j - 1].wall == W3_3T || _tiles[i][j - 1].wall == W3_2RL) ||
					(_tiles[i][j + 1].wall == W3_B || _tiles[i][j + 1].wall == W3_RB || _tiles[i][j + 1].wall == W3_LB || _tiles[i][j + 1].wall == W3_3B || _tiles[i][j + 1].wall == W3_2RL))
				{
					_tiles[i][j].wall == W3_C1;
					_tiles[i][j].wallFrameX = 2;
					_tiles[i][j].wallFrameY = 5;
				}
			}


			if (_tiles[i][j].wall == W3_C1)
			{
				if ((_tiles[i - 1][j].wall == W3_C1 || _tiles[i - 1][j].wall == W3_C2) &&
					(_tiles[i + 1][j].wall == W3_C1 || _tiles[i + 1][j].wall == W3_C2) &&
					(_tiles[i][j - 1].wall == W3_C1 || _tiles[i][j - 1].wall == W3_C2) &&
					(_tiles[i][j + 1].wall == W3_C1 || _tiles[i][j + 1].wall == W3_C2))
				{

					_tiles[i][j].wall == W3_C2;
					_tiles[i][j].wallFrameX = 3;
					_tiles[i][j].wallFrameY = 5;

				}
			}


			//벽 지웠을경우

			if (_tiles[i][j].wall == W_2BT || _tiles[i][j].wall == W_2RL || _tiles[i][j].wall == W_3B || _tiles[i][j].wall == W_3L || _tiles[i][j].wall == W_3R ||
				_tiles[i][j].wall == W_3T || _tiles[i][j].wall == W_4 || _tiles[i][j].wall == W_B || _tiles[i][j].wall == W_L || _tiles[i][j].wall == W_LB ||
				_tiles[i][j].wall == W_LT || _tiles[i][j].wall == W_R || _tiles[i][j].wall == W_RB || _tiles[i][j].wall == W_ROOF || _tiles[i][j].wall == W_RT
				|| _tiles[i][j].wall == W_T)
			{
				_tiles[i][j].terrain = TR_BREAK;
				_tiles[i][j].terrainFrameX = 4;
				_tiles[i][j].terrainFrameY = 1;
			}
			else if (_tiles[i][j].wall == W3_2BT || _tiles[i][j].wall == W3_2RL || _tiles[i][j].wall == W3_3B || _tiles[i][j].wall == W3_3L || _tiles[i][j].wall == W3_3R ||
				_tiles[i][j].wall == W3_3T || _tiles[i][j].wall == W3_4 || _tiles[i][j].wall == W3_B || _tiles[i][j].wall == W3_C || _tiles[i][j].wall == W3_C1 ||
				_tiles[i][j].wall == W3_C2 || _tiles[i][j].wall == W3_L || _tiles[i][j].wall == W3_LB || _tiles[i][j].wall == W3_LT || _tiles[i][j].wall == W3_R ||
				_tiles[i][j].wall == W3_RB || _tiles[i][j].wall == W3_RT || _tiles[i][j].wall == W3_T)
			{
				_tiles[i][j].terrain = T2R_BREAK;
				_tiles[i][j].terrainFrameX = 0;
				_tiles[i][j].terrainFrameY = 4;
			}

			//1stage
			//오른쪽
			if (_tiles[i][j].wall == W_R || _tiles[i][j].wall == W_RB || _tiles[i][j].wall == W_RT)
			{

				if (_tiles[i][j + 1].wall == WALL_NONE && _tiles[i][j - 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_3R;
					_tiles[i][j].wallFrameX = 0;
					_tiles[i][j].wallFrameY = 2;
				}
				else if (_tiles[i][j + 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_RB;
					_tiles[i][j].wallFrameX = 0;
					_tiles[i][j].wallFrameY = 1;
				}
				else if (_tiles[i][j - 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_RT;
					_tiles[i][j].wallFrameX = 5;
					_tiles[i][j].wallFrameY = 0;
				}

			}

			//왼쪽
			if (_tiles[i][j].wall == W_L || _tiles[i][j].wall == W_LB || _tiles[i][j].wall == W_LT)
			{
				if (_tiles[i][j + 1].wall == WALL_NONE && _tiles[i][j - 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_3L;
					_tiles[i][j].wallFrameX = 4;
					_tiles[i][j].wallFrameY = 1;
				}
				else if (_tiles[i][j + 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_LB;
					_tiles[i][j].wallFrameX = 2;
					_tiles[i][j].wallFrameY = 0;
				}
				else if (_tiles[i][j - 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_LT;
					_tiles[i][j].wallFrameX = 3;
					_tiles[i][j].wallFrameY = 0;
				}
			}


			//아래
			if (_tiles[i][j].wall == W_B || _tiles[i][j].wall == W_LB || _tiles[i][j].wall == W_RB)
			{

				if (_tiles[i - 1][j].wall == WALL_NONE && _tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_3B;
					_tiles[i][j].wallFrameX = 3;
					_tiles[i][j].wallFrameY = 1;
				}
				else if (_tiles[i - 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_LB;
					_tiles[i][j].wallFrameX = 2;
					_tiles[i][j].wallFrameY = 0;
				}
				else if (_tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_RB;
					_tiles[i][j].wallFrameX = 0;
					_tiles[i][j].wallFrameY = 1;
				}
			}

			//위
			if (_tiles[i][j].wall == W_T || _tiles[i][j].wall == W_LT || _tiles[i][j].wall == W_RT)
			{

				if (_tiles[i - 1][j].wall == WALL_NONE && _tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_3T;
					_tiles[i][j].wallFrameX = 5;
					_tiles[i][j].wallFrameY = 1;
				}
				else if (_tiles[i - 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_LT;
					_tiles[i][j].wallFrameX = 3;
					_tiles[i][j].wallFrameY = 0;
				}
				else if (_tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_RT;
					_tiles[i][j].wallFrameX = 5;
					_tiles[i][j].wallFrameY = 0;
				}
			}

			//천장
			if (_tiles[i][j].wall == W_ROOF)
			{
				if (_tiles[i - 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_L;
					_tiles[i][j].wallFrameX = 1;
					_tiles[i][j].wallFrameY = 0;
				}
				if (_tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_R;
					_tiles[i][j].wallFrameX = 4;
					_tiles[i][j].wallFrameY = 0;
				}
				if (_tiles[i][j - 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_T;
					_tiles[i][j].wallFrameX = 2;
					_tiles[i][j].wallFrameY = 1;
				}
				if (_tiles[i][j + 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_B;
					_tiles[i][j].wallFrameX = 0;
					_tiles[i][j].wallFrameY = 0;
				}

			}



			//2방
			if (_tiles[i][j].wall == W_T || _tiles[i][j].wall == W_B)
			{
				if (_tiles[i][j - 1].wall == WALL_NONE && _tiles[i][j + 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_2BT;
					_tiles[i][j].wallFrameX = 2;
					_tiles[i][j].wallFrameY = 2;
				}
			}

			if (_tiles[i][j].wall == W_R || _tiles[i][j].wall == W_L)
			{
				if (_tiles[i - 1][j].wall == WALL_NONE && _tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_2RL;
					_tiles[i][j].wallFrameX = 3;
					_tiles[i][j].wallFrameY = 2;
				}
			}


			if (_tiles[i][j].wall == W_2BT)
			{
				if (_tiles[i - 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_3L;
					_tiles[i][j].wallFrameX = 4;
					_tiles[i][j].wallFrameY = 1;
				}
				if (_tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_3R;
					_tiles[i][j].wallFrameX = 0;
					_tiles[i][j].wallFrameY = 2;
				}

			}

			if (_tiles[i][j].wall == W_2RL)
			{
				if (_tiles[i][j - 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_3T;
					_tiles[i][j].wallFrameX = 5;
					_tiles[i][j].wallFrameY = 1;
				}
				if (_tiles[i][j + 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_3B;
					_tiles[i][j].wallFrameX = 3;
					_tiles[i][j].wallFrameY = 1;
				}

			}


			if (_tiles[i][j].wall == W_3B || _tiles[i][j].wall == W_3T || _tiles[i][j].wall == W_3L || _tiles[i][j].wall == W_3R)
			{
				if (_tiles[i - 1][j].wall == WALL_NONE && _tiles[i + 1][j].wall == WALL_NONE && _tiles[i][j - 1].wall == WALL_NONE && _tiles[i][j + 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W_4;
					_tiles[i][j].wallFrameX = 1;
					_tiles[i][j].wallFrameY = 2;
				}
			}

			//stage 2

			//아래

			if (_tiles[i][j].wall == W2_R || _tiles[i][j].wall == W2_R2 || _tiles[i][j].wall == W2_R3)
			{
				if (_tiles[i][j + 1].wall == WALL_NONE)
				{
					if (_tiles[i][j].wall == W2_R)
					{
						_tiles[i][j].wall = W2_B;
						_tiles[i][j].wallFrameX = 0;
						_tiles[i][j].wallFrameY = 3;
					}
					else if (_tiles[i][j].wall == W2_R2)
					{
						_tiles[i][j].wall = W2_B1;
						_tiles[i][j].wallFrameX = 1;
						_tiles[i][j].wallFrameY = 3;
					}
					else if (_tiles[i][j].wall == W2_R3)
					{
						_tiles[i][j].wall = W2_B2;
						_tiles[i][j].wallFrameX = 2;
						_tiles[i][j].wallFrameY = 3;
					}
				}
			}



			//stage 3
			//오른쪽
			if (_tiles[i][j].wall == W3_R || _tiles[i][j].wall == W3_RB || _tiles[i][j].wall == W3_RT)
			{

				if (_tiles[i][j + 1].wall == WALL_NONE && _tiles[i][j - 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_3R;
					_tiles[i][j].wallFrameX = 2;
					_tiles[i][j].wallFrameY = 6;
				}
				else if (_tiles[i][j + 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_RB;
					_tiles[i][j].wallFrameX = 5;
					_tiles[i][j].wallFrameY = 4;
				}
				else if (_tiles[i][j - 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_RT;
					_tiles[i][j].wallFrameX = 0;
					_tiles[i][j].wallFrameY = 5;
				}

			}

			//왼쪽
			if (_tiles[i][j].wall == W3_L || _tiles[i][j].wall == W3_LB || _tiles[i][j].wall == W3_LT)
			{
				if (_tiles[i][j + 1].wall == WALL_NONE && _tiles[i][j - 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_3L;
					_tiles[i][j].wallFrameX = 0;
					_tiles[i][j].wallFrameY = 6;
				}
				else if (_tiles[i][j + 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_LB;
					_tiles[i][j].wallFrameX = 2;
					_tiles[i][j].wallFrameY = 4;
				}
				else if (_tiles[i][j - 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_LT;
					_tiles[i][j].wallFrameX = 3;
					_tiles[i][j].wallFrameY = 4;
				}
			}


			//아래
			if (_tiles[i][j].wall == W3_B || _tiles[i][j].wall == W3_LB || _tiles[i][j].wall == W3_RB)
			{

				if (_tiles[i - 1][j].wall == WALL_NONE && _tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_3B;
					_tiles[i][j].wallFrameX = 5;
					_tiles[i][j].wallFrameY = 5;
				}
				else if (_tiles[i - 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_LB;
					_tiles[i][j].wallFrameX = 2;
					_tiles[i][j].wallFrameY = 4;
				}
				else if (_tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_RB;
					_tiles[i][j].wallFrameX = 5;
					_tiles[i][j].wallFrameY = 4;
				}
			}

			//위
			if (_tiles[i][j].wall == W3_T || _tiles[i][j].wall == W3_LT || _tiles[i][j].wall == W3_RT)
			{

				if (_tiles[i - 1][j].wall == WALL_NONE && _tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_3T;
					_tiles[i][j].wallFrameX = 1;
					_tiles[i][j].wallFrameY = 6;
				}
				else if (_tiles[i - 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_LT;
					_tiles[i][j].wallFrameX = 3;
					_tiles[i][j].wallFrameY = 4;
				}
				else if (_tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_RT;
					_tiles[i][j].wallFrameX = 0;
					_tiles[i][j].wallFrameY = 5;
				}
			}

			//천장
			if (_tiles[i][j].wall == W3_C || _tiles[i][j].wall == W3_C1 || _tiles[i][j].wall == W3_C2)
			{
				if (_tiles[i - 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_L;
					_tiles[i][j].wallFrameX = 1;
					_tiles[i][j].wallFrameY = 4;
				}
				if (_tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_R;
					_tiles[i][j].wallFrameX = 4;
					_tiles[i][j].wallFrameY = 4;
				}
				if (_tiles[i][j - 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_T;
					_tiles[i][j].wallFrameX = 4;
					_tiles[i][j].wallFrameY = 5;
				}
				if (_tiles[i][j + 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_B;
					_tiles[i][j].wallFrameX = 0;
					_tiles[i][j].wallFrameY = 4;
				}

			}


			//2방
			if (_tiles[i][j].wall == W3_T || _tiles[i][j].wall == W3_B)
			{
				if (_tiles[i][j - 1].wall == WALL_NONE && _tiles[i][j + 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_2BT;
					_tiles[i][j].wallFrameX = 4;
					_tiles[i][j].wallFrameY = 6;
				}
			}

			if (_tiles[i][j].wall == W3_R || _tiles[i][j].wall == W3_L)
			{
				if (_tiles[i - 1][j].wall == WALL_NONE && _tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_2RL;
					_tiles[i][j].wallFrameX = 5;
					_tiles[i][j].wallFrameY = 6;
				}
			}


			if (_tiles[i][j].wall == W3_2BT)
			{
				if (_tiles[i - 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_3L;
					_tiles[i][j].wallFrameX = 0;
					_tiles[i][j].wallFrameY = 6;
				}
				if (_tiles[i + 1][j].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_3R;
					_tiles[i][j].wallFrameX = 2;
					_tiles[i][j].wallFrameY = 6;
				}

			}

			if (_tiles[i][j].wall == W3_2RL)
			{
				if (_tiles[i][j - 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_3T;
					_tiles[i][j].wallFrameX = 1;
					_tiles[i][j].wallFrameY = 6;
				}
				if (_tiles[i][j + 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_3B;
					_tiles[i][j].wallFrameX = 5;
					_tiles[i][j].wallFrameY = 5;
				}

			}

			if (_tiles[i][j].wall == W3_3B || _tiles[i][j].wall == W3_3T || _tiles[i][j].wall == W3_3L || _tiles[i][j].wall == W3_3R)
			{
				if (_tiles[i - 1][j].wall == WALL_NONE && _tiles[i + 1][j].wall == WALL_NONE && _tiles[i][j - 1].wall == WALL_NONE && _tiles[i][j + 1].wall == WALL_NONE)
				{
					_tiles[i][j].wall = W3_4;
					_tiles[i][j].wallFrameX = 3;
					_tiles[i][j].wallFrameY = 6;
				}
			}
		}
	}
}
void mapManager::setTileRect()
{
	for (int i = 0; i < TILEX;++i) {
		for (int j = 0; j < TILEY; ++j) {
			_tiles[i][j].rc = RectMake(i * TILESIZE,j * TILESIZE,TILESIZE,TILESIZE);
		}
	}
}
void mapManager::setWidthCount(int i)
{
	width_count = i;
	if (width_count <= 1 ) {
		width_count = 1;
	}
	if (width_count >= TILEX) {
		width_count = TILEX;
	}
}
void mapManager::setHeightCount(int i)
{
	height_count = i;
	if (height_count <= 1) {
		height_count = 1;
	}
	if (height_count >= TILEY) {
		height_count = TILEY;
	}
}

void mapManager::setOpenTiles()
{
	//clear
	_openTiles.clear();
	//현재 tiles에서 wall_none 인 타일의 중점만 벡터에 추가해준다.
	for (int i = 0; i < TILEX; ++i) {
		for (int j = 0; j < TILEY; ++j) {
			//벽이 없으면 오픈타일이니, 이것의 point를 사용한다.
			if (_tiles[i][j].wall == WALL_NONE) {
				POINT temp_pt = PointMake(
					_tiles[i][j].rc.left + (_tiles[i][j].rc.right - _tiles[i][j].rc.left) / 2,
					_tiles[i][j].rc.top + (_tiles[i][j].rc.bottom - _tiles[i][j].rc.top) / 2);
				_openTiles.push_back(temp_pt);
			}
		}
	}



}

vector<POINT> mapManager::getOpenTiles()
{
	return _openTiles;
}

tagCurrentTile mapManager::getEnemyTileset(int type)
{
	tagCurrentTile temp;
	ENEMYTYPE _enemyType = (ENEMYTYPE)type;


	if (_enemyType == BIGBANDIT || _enemyType == BIGDOG) {
		temp.img = IMAGEMANAGER->findImage("bossset");
	}
	else {
		temp.img = IMAGEMANAGER->findImage("enemyset");
	}

	switch (_enemyType)
	{
	case BIGBANDIT:
		temp.x = 0;
		temp.y = 0;
		break;
	case BIGDOG:
		temp.x = 1;
		temp.y = 0;
		break;
	case BANDIT:
		temp.x = 0;
		temp.y = 0;
		break;
	case MAGGOT:
		temp.x = 1;
		temp.y = 0;
		break;
	case BIGMAGGOT:
		temp.x = 2;
		temp.y = 0;
		break;
	case GREENMAGGOT:
		temp.x = 3;
		temp.y = 0;
		break;
	case MAGGOTNEST:
		temp.x = 4;
		temp.y = 0;
		break;
	case SCOLPION:
		temp.x = 5;
		temp.y = 0;
		break;
	case RAT:
		temp.x = 0;
		temp.y = 1;
		break;
	case GREENRAT:
		temp.x = 1;
		temp.y = 1;
		break;
	case BIGRAT:
		temp.x = 2;
		temp.y = 1;
		break;
	case FROG:
		temp.x = 3;
		temp.y = 1;
		break;
	case GREENFROG:
		temp.x = 4;
		temp.y = 1;
		break;
	case GATOR:
		temp.x = 0;
		temp.y = 2;
		break;
	case RAVEN:
		temp.x = 1;
		temp.y = 2;
		break;
	case ASSASSIN:
		temp.x = 2;
		temp.y = 2;
		break;
	case SNIPER:
		temp.x = 3;
		temp.y = 2;
		break;
	case SALAMADER:
		temp.x = 4;
		temp.y = 2;
		break;
	default:
		break;
	}
	return temp;
}

int mapManager::getEnemyType(int x, int y)
{
	ENEMYTYPE temp = BANDIT;

	if (_Select == DrawEnemy) {
		if (x == 0 && y == 0) {
			temp = BANDIT;
		}
		else if (x == 1 && y == 0) {
			temp = MAGGOT;
		}
		else if (x == 2 && y == 0) {
			temp = BIGMAGGOT;
		}
		else if (x == 3 && y == 0) {
			temp = GREENMAGGOT;
		}
		else if (x == 4 && y == 0) {
			temp = MAGGOTNEST;
		}
		else if (x == 5 && y == 0) {
			temp = SCOLPION;
		}
		else if (x == 0 && y == 1) {
			temp = RAT;
		}
		else if (x == 1 && y == 1) {
			temp = GREENRAT;
		}
		else if (x == 2 && y == 1) {
			temp = BIGRAT;
		}
		else if (x == 3 && y == 1) {
			temp = FROG;
		}
		else if (x == 4 && y == 1) {
			temp = GREENFROG;
		}
		else if (x == 0 && y == 2) {
			temp = GATOR;
		}
		else if (x == 1 && y == 2) {
			temp = RAVEN;
		}
		else if (x == 2 && y == 2) {
			temp = ASSASSIN;
		}
		else if (x == 3 && y == 2) {
			temp = SNIPER;
		}
		else if (x == 4 && y == 2) {
			temp = SALAMADER;
		}
	}
	else if (_Select = DrawBoss) {
		if ((x >= 0 && x <= 2) && (y >= 0 && y <= 2)) {
			temp = BIGBANDIT;
		}
		else if ((x >= 3 && x <= 5) && (y >= 0 && y <= 2)) {
			temp = BIGDOG;
		}
	}

	return temp;
}

//
//void mapManager::setShowTileMemory()
//{
//	_showTile = new showTile*[width_count];
//	for (int i = 0; i < width_count; ++i) {
//		_showTile[i] = new showTile[height_count];
//	}
//}
TERRAIN mapManager::terrainSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return TR_C;
	if (frameX == 1 && frameY == 0) return TR_C2;
	if (frameX == 2 && frameY == 0) return TR2_C;
	if (frameX == 3 && frameY == 0) return TR2_C1;
	if (frameX == 4 && frameY == 0) return TR2_C2;
	if (frameX == 0 && frameY == 1) return TR3_1;
	if (frameX == 1 && frameY == 1) return TR3_2;
	if (frameX == 2 && frameY == 1) return TR3_3;
	if (frameX == 3 && frameY == 1) return TR3_4;
	if (frameX == 4 && frameY == 1) return TR_BREAK;


	if (frameX == 0 && frameY == 2) return T2R_C;
	if (frameX == 1 && frameY == 2) return T2R_C2;
	if (frameX == 2 && frameY == 2) return T2R_C3;
	if (frameX == 3 && frameY == 2) return T2R_C4;
	if (frameX == 4 && frameY == 2) return T2R_C5;
	if (frameX == 0 && frameY == 3) return T2R_P;
	if (frameX == 1 && frameY == 3) return T2R_P2;
	if (frameX == 2 && frameY == 3) return T2R_P3;
	if (frameX == 3 && frameY == 3) return T2R_H;
	if (frameX == 4 && frameY == 3) return T2R_H2;
	if (frameX == 0 && frameY == 4) return T2R_BREAK;
	if (frameX == 1 && frameY == 4) return T2R_PP;

	if (frameX == 2 && frameY == 4) return T3R_C;
	if (frameX == 3 && frameY == 4) return T3R_C2;
	if (frameX == 4 && frameY == 4) return T3R_C2B;
	if (frameX == 0 && frameY == 5) return T3R_C2R;
	if (frameX == 1 && frameY == 5) return T3R_C2L;
	if (frameX == 2 && frameY == 5) return T3R_C2T;

	return TR_C;
}

OBJECT mapManager::objSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return OBJ_BLOCK1;
	if (frameX == 1 && frameY == 0) return OBJ_BLOCK2;
	if (frameX == 2 && frameY == 0) return OBJ_BLOCK3;
	if (frameX == 3 && frameY == 0) return OBJ_BLOCK4;
	if (frameX == 0 && frameY == 1) return OBJ_BLOCK5;
	if (frameX == 1 && frameY == 1) return OBJ_BLOCK6;
	if (frameX == 2 && frameY == 1) return OBJ_BLOCK7;
	if (frameX == 3 && frameY == 1) return OBJ_BLOCK8;
	if (frameX == 4 && frameY == 1) return OBJ_BLOCK9;

	if (frameX == 0 && frameY == 4) return OBJ_BLOCK11;
	if (frameX == 1 && frameY == 4) return OBJ_BLOCK12;


	if (frameX == 0 && frameY == 2) return OBJ2_BLOCK1;
	if (frameX == 1 && frameY == 2) return OBJ2_BLOCK2;
	if (frameX == 2 && frameY == 2) return OBJ2_BLOCK3;
	if (frameX == 3 && frameY == 2) return OBJ2_BLOCK4;
	if (frameX == 4 && frameY == 2) return OBJ2_BLOCK5;
	if (frameX == 5 && frameY == 2) return OBJ2_BLOCK6;


	if (frameX == 0 && frameY == 3) return OBJ3_BLOCK1;
	if (frameX == 1 && frameY == 3) return OBJ3_BLOCK2;
	if (frameX == 2 && frameY == 3) return OBJ3_BLOCK3;

	if (frameX == 0 && frameY == 6) return OBJ1_SHD;
	if (frameX == 2 && frameY == 6) return OBJ2_SHD;
	if (frameX == 4 && frameY == 6) return OBJ3_SHD;


	return OBJ3_BLOCK1;
}

WALL mapManager::wallSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return W_B;
	if (frameX == 1 && frameY == 0) return W_L;
	if (frameX == 2 && frameY == 0) return W_LB;
	if (frameX == 3 && frameY == 0) return W_LT;
	if (frameX == 4 && frameY == 0) return W_R;
	if (frameX == 5 && frameY == 0) return W_RT;
	if (frameX == 0 && frameY == 1) return W_RB;
	if (frameX == 1 && frameY == 1) return W_ROOF;
	if (frameX == 2 && frameY == 1) return W_T;
	if (frameX == 3 && frameY == 1) return W_3B;
	if (frameX == 4 && frameY == 1) return W_3L;
	if (frameX == 5 && frameY == 1) return W_3T;
	if (frameX == 0 && frameY == 2) return W_3R;
	if (frameX == 1 && frameY == 2) return W_4;
	if (frameX == 2 && frameY == 2) return W_2BT;
	if (frameX == 3 && frameY == 2) return W_2RL;

	if (frameX == 0 && frameY == 3) return W2_B;
	if (frameX == 1 && frameY == 3) return W2_B1;
	if (frameX == 2 && frameY == 3) return W2_B2;
	if (frameX == 3 && frameY == 3) return W2_R;
	if (frameX == 4 && frameY == 3) return W2_R2;
	if (frameX == 5 && frameY == 3) return W2_R3;

	if (frameX == 0 && frameY == 4) return W3_B;
	if (frameX == 1 && frameY == 4) return W3_L;
	if (frameX == 2 && frameY == 4) return W3_LB;
	if (frameX == 3 && frameY == 4) return W3_LT;
	if (frameX == 4 && frameY == 4) return W3_R;
	if (frameX == 5 && frameY == 4) return W3_RB;
	if (frameX == 0 && frameY == 5) return W3_RT;
	if (frameX == 1 && frameY == 5) return W3_C;
	if (frameX == 2 && frameY == 5) return W3_C1;
	if (frameX == 3 && frameY == 5) return W3_C2;
	if (frameX == 4 && frameY == 5) return W3_T;
	if (frameX == 5 && frameY == 5) return W3_3B;
	if (frameX == 0 && frameY == 6) return W3_3L;
	if (frameX == 1 && frameY == 6) return W3_3T;
	if (frameX == 2 && frameY == 6) return W3_3R;
	if (frameX == 3 && frameY == 6) return W3_4;
	if (frameX == 4 && frameY == 6) return W3_2BT;
	if (frameX == 5 && frameY == 6) return W3_2RL;

	return W3_B;
}

POINT mapManager::enemyMove(POINT pt)
{
	//현재 point의 타일 index 위치 
	//(전체 탐색 후, 현재 위치의 타일index를 저장하기 위함)
	int index_x = 0;
	int index_y = 0;

	//다음 움직일 해당 타일의 index
	int next_x = 0;
	int next_y = 0;

	//최소값 찾기 위한 변수
	int min = 1000000;

	//다음 타일의 중점
	POINT nextArea;
	

	//절대경로 (타일 한개의 크기로 나눠서 index를 찾음
	index_x = pt.x / 64;
	index_y = pt.y / 64;

	//전체탐색
	//for (int i = 0; i < TILEX; ++i) {
	//	for (int j = 0; j < TILEY; ++j) {
	//		
	//		//WALL_NONE = 벽이 없다는 것
	//		if (PtInRect(&_tiles[i][j].rc, pt) ) {
	//			//해당 타일 위치 찾음
	//			index_x = i;
	//			index_y = j;
	//			break;
	//		}
	//	}
	//}

	//최솟값 탐색
	for (int i = index_x - 1; i <= index_x + 1; ++i) {
		for (int j = index_y - 1; j <= index_y + 1; ++j) {
			//첫번째, 세번째는 가운데만 = 가로세로만 검색
			if (i == index_x - 1 || i == index_x + 1) {
				if (j != index_y) {
					continue;
				}
			}
			//타일에 벽이 존재하면 continue;
			if (_tiles[i][j].wall != WALL_NONE) {
				continue;
			}
			//현재 자기위치는 continue;
			if (i == index_x && j == index_y) {
				continue;
			}

			//h(x)
			int distance = (int)getDistance(
				PLAYERMANAGER->getPlayer()->getPt().x,
				PLAYERMANAGER->getPlayer()->getPt().y,
				_tiles[i][j].rc.left + (_tiles[i][j].rc.right - _tiles[i][j].rc.left)/2,
				_tiles[i][j].rc.top + (_tiles[i][j].rc.bottom - _tiles[i][j].rc.top)/2
			);
			//f(X) = g(x)+h(x) 비교해서 f(x)가 가장 작은 것으로 index
			if (distance < min) {
				min = distance;
				next_x = i;
				next_y = j;
			}
		}
	}
	nextArea = PointMake(next_x * TILESIZE, next_y * TILESIZE);

	
	return nextArea;
}

POINT mapManager::enemyRandomMove(POINT pt)
{
	POINT nextArea;
	//절대경로 (타일 한개의 크기로 나눠서 index를 찾음
	int index_x = pt.x / 64;
	int index_y = pt.y / 64;
	int rnd = RND->getInt(4);
	
	while (true) {
		int i;
		int j;	
		//3보다 커지면 0 으로 초기화
		if (rnd > 3) {
			rnd = 0;
		}
		//랜덤으로 상, 하, 좌, 우 의 타일로 이동한다.
		switch (rnd)
		{
		case 0://상
			i = index_x;
			j = index_y - 1;
			break;
		case 1://하
			i = index_x;
			j = index_y + 1;
			break;
		case 2://좌
			i = index_x - 1;
			j = index_y;
			break;
		case 3://우
			i = index_x + 1;
			j = index_y;
			break;
		default:
			break;
		}
		//다음 위치에 해당하는 타일이 wall이 있으면 다시
		if (_tiles[i][j].wall != WALL_NONE) {
			rnd++;
			continue;
		}
		else {
			break;
		}
	}


	//랜덤으로 상, 하, 좌, 우 의 타일로 이동한다.
	switch (rnd)
	{
	case 0://상
		nextArea.x = index_x * 64;
		nextArea.y = (index_y - 1) * 64;
		break;
	case 1://하
		nextArea.x = index_x * 64;
		nextArea.y = (index_y + 1) * 64;
		break;
	case 2://좌
		nextArea.x = (index_x - 1) * 64;
		nextArea.y = index_y * 64;
		break;
	case 3://우
		nextArea.x = (index_x + 1) * 64;
		nextArea.y = index_y * 64;
		break;
	default:
		break;
	}
	
	return nextArea;
}

bool mapManager::isStraight(POINT player, POINT enemy)
{
	int startx, starty, endx, endy;
	if (player.x <= enemy.x)
	{
		startx = player.x / 64;
		endx = enemy.x / 64;
	}
	else
	{
		startx = enemy.x / 64;
		endx = player.x / 64;
	}
	if (player.y <= enemy.y)
	{
		starty = player.y / 64;
		endy = enemy.y / 64;
	}
	else
	{
		starty = enemy.y / 64;
		endy = player.y / 64;
	}
	for (int i = startx; i <= endx; i++)
	{
		for (int j = starty; j <= endy; j++)
		{
			if (_tiles[i][j].wall == WALL_NONE) continue;
			if (intersects(_tiles[i][j].rc, player, enemy)) return false;
		}
	}
	return true;
}

bool mapManager::ptIntersect(POINT pt)
{
	int x = pt.x / 64;
	int y = pt.y / 64;

	if (_tiles[x][y].wall == WALL_NONE) return false;
	if (_tiles[x][y].wall != WALL_NONE) return true;
}

void mapManager::createPortal()
{
	portal.rc = RectMakeCenter(getStartPoint().x, getStartPoint().y, portal.img->getWidth(), portal.img->getHeight());
	portal_animation->start();
}

void mapManager::updatePortal()
{
	portal_animation->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void mapManager::erasePortal()
{
	portal.rc = RectMakeCenter(0,0,0,0);
}

void mapManager::renderPortal(HDC hdc)
{
	portal.img->aniRender(hdc,portal.rc.left, portal.rc.top, portal_animation);
}

void mapManager::collisionPortal()
{
	RECT temp;
	//플레이어가 portalRect와 충돌하면, 카드선택씬으로 이동
	if (IntersectRect(&temp, &PLAYERMANAGER->getPlayer()->getRect(), &portal.rc)) {
		SCENEMANAGER->changeScene("카드선택씬");
	}

}