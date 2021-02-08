#pragma once
#include "gameNode.h"
//���� ����� ���� include
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

class clearScene : public gameNode
{
private:
	bool _isStart;
	HWND _clearVideo; //���� ����� ���� �ڵ�

	int _videoCount;
public:
	clearScene();
	~clearScene();
	HRESULT init();
	void release();
	void update();
	void render();

	void KeyManager(); // Ű�Ŵ���
	void VideoPlay(); // ���� ���� �Լ�
	void VideoStop(); // ���� ���� �Լ�
};

