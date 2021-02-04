#pragma once
#include "singletonBase.h"
#include "Player.h"
#include "Fish.h"
#include "Crystal.h"
#include "Eyes.h"
#include "Meiting.h"
#include "Plant.h"

enum PLAYERTYPE
{
	FISH,
	CRYSTAL,
	EYES,
	PLANT,
	MELTING,
	RANDOM
};

class playerManager : public singletonBase<playerManager>
{
private:
	Player* _player;
	
	PLAYERTYPE _playertype;
public:
	playerManager();
	~playerManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void setplayer(PLAYERTYPE playerType, int x, int y);
	void setimage();
	
	//setter
	void setPlayerPosition(POINT pt) { _player->setPT(pt); };
	//getter
	Player* getPlayer() { return _player; };
	PLAYERTYPE getPlayerType() { return _playertype; };
};

