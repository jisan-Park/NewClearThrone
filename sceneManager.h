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
	//bar ��ġ
	int x, y;
	//frontBar ����
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

	//���߰� �Լ�
	gameNode* addScene(string sceneName, gameNode* scene);

	//�� ���� �Լ�
	HRESULT changeScene(string sceneName);

	sceneManager() {};
	~sceneManager() {};
};

