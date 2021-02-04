#pragma once
#include "gameNode.h"

#define LOADINGMAX 1000

class progressBar;

class loadingScene : public gameNode
{
private:


public:
	loadingScene();
	~loadingScene();

	int _currentCount;

	HRESULT init();
	void release();
	void update();
	void render();
};
static DWORD CALLBACK threadFunction(LPVOID lpParameter);