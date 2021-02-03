#pragma once
#include "singletonBase.h"
#include <string>
#include <map>
struct tagImage {
	image* img;
	RECT rc;
	int x, y;
};

struct tagAlphaImage {
	tagImage info;
	int alpha;
};

struct tagVolume {
	RECT rc;
	int x, y;
	int width;
	image* backBar;
	image* frontBar;
	image* button;
};

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;

	mapSceneList _mSceneList;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//¾ÀÃß°¡ ÇÔ¼ö
	gameNode* addScene(string sceneName, gameNode* scene);

	//¾À º¯°æ ÇÔ¼ö
	HRESULT changeScene(string sceneName);

	sceneManager() {};
	~sceneManager() {};
};

