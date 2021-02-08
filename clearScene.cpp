#include "stdafx.h"
#include "clearScene.h"

clearScene::clearScene()
{
}

clearScene::~clearScene()
{
}

HRESULT clearScene::init()
{

	//playGround render 처리 하기 위함
	SCENEMANAGER->setIsVideoPlay(true);

	_isStart = false;


	return S_OK;
}

void clearScene::release()
{
}

void clearScene::update()
{
	if (!_isStart)
	{
		VideoPlay();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		VideoStop();
		_isStart = false;

		//playGround render 처리 하기 위함
		SCENEMANAGER->setIsVideoPlay(false);
		SCENEMANAGER->changeScene("시작씬");
	}
}

void clearScene::render()
{

}

void clearScene::KeyManager()
{

}

void clearScene::VideoPlay()
{
	_videoCount++;


	if (_videoCount == 10) // 한번만 실행되야 하기 때문
	{
		_clearVideo = MCIWndCreate(_hWnd, NULL, MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU | WS_VISIBLE | WS_CHILD, "video/credit.wmv");
		SetWindowPos(_clearVideo, NULL, 0, 0, WINSIZEX, WINSIZEY, SWP_NOZORDER | SWP_NOMOVE);
		MCIWndPlay(_clearVideo);
		_isStart = true;
	}

}

void clearScene::VideoStop()
{
	MCIWndClose(_clearVideo);
	MCIWndDestroy(_clearVideo);
}
