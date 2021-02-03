#pragma once
#include "gameNode.h"
class settingScene : public gameNode
{
private:
	//back Scene
	tagAlphaImage back;

	//volume front bar
	tagVolume master;
	tagVolume music;
	tagVolume sfx;

public:
	HRESULT init();
	void update();
	void release();
	void render();

	void setImage();
};

