#pragma once
#include "gameNode.h"

class StartScene : public gameNode
{
private:
	tagAlphaImage _logo;
	tagAlphaImage _pressEnter;
	float interval;

public:
	HRESULT init();
	void update();
	void release();
	void render();

	void setImage();
};

