#pragma once
#include "gameNode.h"
class gameScene : public gameNode
{
private:
	int _sound1;
	int _sound2;
	int _sound3;

public:
	HRESULT init();
	void update();
	void release();
	void render();
};

