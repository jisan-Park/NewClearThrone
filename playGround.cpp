#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);  
	IMAGEMANAGER->addImage("mouse_aim","image/ui/mouse_aim.bmp",40,40,true,RGB(255,0,255));

	SCENEMANAGER->addScene("½ÃÀÛ¾À", new StartScene);
	SCENEMANAGER->addScene("¸ÞÀÎ¸Þ´º¾À", new mainmenuScene);
	SCENEMANAGER->addScene("°ÔÀÓ¾À", new gameScene);
	SCENEMANAGER->addScene("Ä¿½ºÅÒ¾À", new customScene);
	SCENEMANAGER->addScene("¸ÊÅø¾À", new maptoolScene);
	SCENEMANAGER->addScene("¼ÂÆÃ¾À", new settingScene);
	SCENEMANAGER->addScene("¼¿·ºÆ®¾À", new selectScene);
	SCENEMANAGER->addScene("Ä«µå¼±ÅÃ¾À", new cardselectScene);
	SCENEMANAGER->addScene("Å¬¸®¾î¾À", new clearScene);

	SCENEMANAGER->changeScene("½ÃÀÛ¾À");

	return S_OK;
}


void playGround::release()
{
	gameNode::release();
}

void playGround::update()
{
	gameNode::update();

	EFFECTMANAGER->update();
	SCENEMANAGER->update();
}


void playGround::render()
{
	if (!SCENEMANAGER->getIsVideoPlay()) {
		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		//================ À§¿¡ °ÇµéÁö ¸¶¶ó ==============================

		SCENEMANAGER->render();

		if (KEYMANAGER->isToggleKey(VK_F1)) {
			TIMEMANAGER->render(getMemDC());
		}
		//================= ¾Æ·¡µµ °ÇµéÁö ¸¶¶ó ==============================
		_backBuffer->render(getHDC());
	}
}