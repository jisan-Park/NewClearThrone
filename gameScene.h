#pragma once
#include "gameNode.h"
class gameScene : public gameNode
{
private:
public:
	HRESULT init();
	void update();
	void release();
	void render();
};

