#pragma once
#include "gameNode.h"
class mainmenuScene : public gameNode
{
private:
	tagAlphaImage selectMenu[5];

	tagAlphaImage _gamePlay;
	tagAlphaImage _customPlay;
	tagAlphaImage _maptool;
	tagAlphaImage _setting;
	tagAlphaImage _quit;
public:
	HRESULT init();
	void update();
	void release();
	void render();

	void setImage();
};

