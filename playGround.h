#pragma once
#include "gameNode.h"
#include "StartScene.h"
#include "mainmenuScene.h"
#include "settingScene.h"
#include "maptoolScene.h"
#include "gameScene.h"
#include "customScene.h"
#include "selectScene.h"

class playGround : public gameNode
{
private:

public:
	playGround();
	~playGround();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
};