#pragma once
#include "gameNode.h"
class customScene : public gameNode
{
private:

public:
	HRESULT init();
	void update();
	void release();
	void render();
};

