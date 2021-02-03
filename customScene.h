#pragma once
#include "gameNode.h"
class customScene : public gameNode
{
private:
	RECT mouse;
public:
	HRESULT init();
	void update();
	void release();
	void render();
};

