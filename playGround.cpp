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

	SCENEMANAGER->addScene("���۾�", new StartScene);
	SCENEMANAGER->addScene("���θ޴���", new mainmenuScene);
	SCENEMANAGER->addScene("���Ӿ�", new gameScene);
	SCENEMANAGER->addScene("Ŀ���Ҿ�", new customScene);
	SCENEMANAGER->addScene("������", new maptoolScene);
	SCENEMANAGER->addScene("���þ�", new settingScene);
	SCENEMANAGER->addScene("����Ʈ��", new selectScene);
	SCENEMANAGER->addScene("ī�弱�þ�", new cardselectScene);
	SCENEMANAGER->addScene("Ŭ�����", new clearScene);

	SCENEMANAGER->changeScene("���۾�");

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
		//================ ���� �ǵ��� ���� ==============================

		SCENEMANAGER->render();

		if (KEYMANAGER->isToggleKey(VK_F1)) {
			TIMEMANAGER->render(getMemDC());
		}
		//================= �Ʒ��� �ǵ��� ���� ==============================
		_backBuffer->render(getHDC());
	}
}