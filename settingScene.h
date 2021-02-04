#pragma once
#include "gameNode.h"
class settingScene : public gameNode
{
private:
	

public:
	HRESULT init();
	void update();
	void release();
	void render();

	void setImage();
};

