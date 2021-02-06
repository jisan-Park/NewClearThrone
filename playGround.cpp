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

	SCENEMANAGER->addScene("시작씬", new StartScene);
	SCENEMANAGER->addScene("메인메뉴씬", new mainmenuScene);
	SCENEMANAGER->addScene("게임씬", new gameScene);
	SCENEMANAGER->addScene("커스텀씬", new customScene);
	SCENEMANAGER->addScene("맵툴씬", new maptoolScene);
	SCENEMANAGER->addScene("셋팅씬", new settingScene);
	SCENEMANAGER->addScene("셀렉트씬", new selectScene);
	SCENEMANAGER->addScene("카드선택씬", new cardselectScene);


	SOUNDMANAGER->addSound("메인메뉴", "sound/배경/메인메뉴.mp3", true, true);
	SOUNDMANAGER->addSound("캐릭터선택", "sound/배경/캐릭터선택.mp3", true, true);
	SOUNDMANAGER->addSound("스테이지1", "sound/배경/스테이지1.mp3", true, true);
	SOUNDMANAGER->addSound("스테이지2", "sound/배경/스테이지2.mp3", true, true);
	SOUNDMANAGER->addSound("스테이지3", "sound/배경/스테이지3.mp3", true, true);

	SOUNDMANAGER->addSound("멜팅죽을떄", "sound/플레이어 사망/멜팅죽을때.mp3", false, false);
	SOUNDMANAGER->addSound("아이즈죽을때", "sound/플레이어 사망/아이즈죽을때.mp3", false, false);
	SOUNDMANAGER->addSound("크리스탈죽을때", "sound/플레이어 사망/크리스탈죽을때.mp3", false, false);
	SOUNDMANAGER->addSound("플랜트죽을때", "sound/플레이어 사망/플랜트죽을대.mp3", false, false);
	SOUNDMANAGER->addSound("피쉬죽을때", "sound/플레이어 사망/피쉬죽을때.mp3", false, false);

	SOUNDMANAGER->addSound("아이즈 스킬", "sound/아이즈 스킬.mp3", false, false);
	SOUNDMANAGER->addSound("크리스탈 스킬", "sound/크리스탈스킬.mp3", false, false);
	SOUNDMANAGER->addSound("플랜트 스킬", "sound/플레이어 사망/플랜트 스킬.mp3", false, false);
	SOUNDMANAGER->addSound("피쉬 스킬", "sound/플레이어 사망/피쉬 스킬.mp3", false, false);

	SOUNDMANAGER->addSound("클릭소리", "sound/효과음/클릭소리.mp3", false, false);
	SOUNDMANAGER->addSound("폭발사운드", "sound/효과음/폭빌사운드.mp3", false, false);
	
	SOUNDMANAGER->addSound("멜팅 선택", "sound/효과음/캐릭터 선택/멜팅 선택.mp3", false, false);
	SOUNDMANAGER->addSound("플랜트선택", "sound/효과음/캐릭터 선택/플랜트 선택.mp3", false, false);
	SOUNDMANAGER->addSound("아이즈선택", "sound/효과음/캐릭터 선택/아이즈 선택.mp3", false, false);
	SOUNDMANAGER->addSound("크리스탈 선택", "sound/효과음/캐릭터 선택/크리스탈선택.mp3", false, false);
	SOUNDMANAGER->addSound("피쉬 선택", "sound/효과음/캐릭터 선택/피쉬 선택.mp3", false, false);

	SOUNDMANAGER->addSound("까마귀 맞았을때", "sound/효과음/에너미/까마귀/까마귀 맞았을때.mp3", false, false);
	SOUNDMANAGER->addSound("까마귀1", "sound/효과음/에너미/까마귀/까마귀1.mp3", false, false);
	SOUNDMANAGER->addSound("까마귀2", "sound/효과음/에너미/까마귀/까마귀2.mp3", false, false);
	
	SOUNDMANAGER->addSound("도마뱀 불뿜기", "sound/효과음/에너미/도마뱀/불뿜기.mp3", false, true);
	
	SOUNDMANAGER->addSound("잡몹 죽을때1", "sound/효과음/에너미/잡몹/잡몹죽을때1.mp3", false, false);
	SOUNDMANAGER->addSound("잡몹 죽을때2", "sound/효과음/에너미/잡몹/잡몹죽을때2.mp3", false, false);

	SOUNDMANAGER->addSound("빅독도는거", "sound/효과음/에너미/빅독돌면서총쏘는.mp3", false, true);
	SOUNDMANAGER->addSound("빅독 등장", "sound/효과음/에너미/빅독등장.mp3", false, false);
	SOUNDMANAGER->addSound("빅밴딧 등장", "sound/효과음/에너미/빅밴딧등장1.mp3", false, false);
	
	SOUNDMANAGER->addSound("권총", "sound/효과음/무기/권총.mp3", false, false);
	SOUNDMANAGER->addSound("단발 쎈거", "sound/효과음/무기/단발 쎈거.mp3", false, false);
	SOUNDMANAGER->addSound("둔기", "sound/효과음/무기/둔기.mp3", false, false);
	SOUNDMANAGER->addSound("레이저", "sound/효과음/무기/레이저.mp3", false, false);
	SOUNDMANAGER->addSound("렌치", "sound/효과음/무기/렌치.mp3", false, false);
	SOUNDMANAGER->addSound("쇠소리", "sound/효과음/무기/쇠소리.mp3", false, false);
	SOUNDMANAGER->addSound("약한총", "sound/효과음/무기/약한총.mp3", false, false);
	SOUNDMANAGER->addSound("재장전", "sound/효과음/무기/재장전.mp3", false, false);
	SOUNDMANAGER->addSound("칼", "sound/효과음/무기/칼.mp3", false, false);




	SCENEMANAGER->changeScene("시작씬");

	return S_OK;
}


void playGround::release()
{
	gameNode::release();
}

void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	SCENEMANAGER->render();

	if (KEYMANAGER->isToggleKey(VK_F1)) {
		TIMEMANAGER->render(getMemDC());
	}
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}