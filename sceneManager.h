#pragma once
#include "singletonBase.h"
#include <string>
#include <map>
struct tagImage {
	image* img;
	RECT rc;
	int x, y;
	int currentFrameX;
	int currentFrameY;
};

struct tagAlphaImage {
	tagImage info;
	int alpha;
};

struct tagVolume {
	RECT rc;
	//bar 위치
	int x, y;
	//frontBar 길이
	int width;
	image* backBar;
	image* frontBar;
	image* button;
	POINT center;
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

	bool _isVideoPlay;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setIsVideoPlay(bool b) { _isVideoPlay = b; };
	bool getIsVideoPlay() { return _isVideoPlay; };

	//씬추가 함수
	gameNode* addScene(string sceneName, gameNode* scene);

	//씬 변경 함수
	HRESULT changeScene(string sceneName);

	sceneManager() {};
	~sceneManager() {};
};

