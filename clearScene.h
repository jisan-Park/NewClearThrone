#pragma once
#include "gameNode.h"
//비디오 재생을 위한 include
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

class clearScene : public gameNode
{
private:
	bool _isStart;
	HWND _clearVideo; //비디오 출력을 위한 핸들

	int _videoCount;
public:
	clearScene();
	~clearScene();
	HRESULT init();
	void release();
	void update();
	void render();

	void KeyManager(); // 키매니저
	void VideoPlay(); // 비디오 실행 함수
	void VideoStop(); // 비디오 정지 함수
};

