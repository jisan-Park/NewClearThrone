#pragma once
#include "gameNode.h"


class maptoolScene : public gameNode
{
private:
	tagAlphaImage selectTile[6];
	tagAlphaImage selectBtn[7];

public:
	HRESULT init();
	void update();
	void release();
	void render();

	void setImage();
	void keyupdate();
};

