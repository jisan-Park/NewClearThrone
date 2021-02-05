#include "stdafx.h"
#include "cardselectScene.h"


cardselectScene::cardselectScene()
{
	AddFontResource("title.ttf");
	AddFontResource("dc.ttf");
}

cardselectScene::~cardselectScene()
{
}

HRESULT cardselectScene::init()
{
	setImage();
	randomCard();

	_x = 350;
	_y = 350;

	//임시지정
	_playerN = 0;

	for (int i = 0; i < 4; i++)
	{
		_a[i] = 0;
		_aCard[i].rc = RectMakeCenter((WINSIZEX / 2 - 205) + 130 * i, WINSIZEY - 75, 108, 144);
	}


	//텍스트
	titleI();
	disI();

	return S_OK;
}

void cardselectScene::update()
{
	ptInCard();
	move();


	KEYANIMANAGER->update();
}


void cardselectScene::release()
{
	RemoveFontResource("title.ttf");
	RemoveFontResource("dc.ttf");
}

void cardselectScene::render()
{
	IMAGEMANAGER->findImage("background")->aniRender(getMemDC(), 0, 0, KEYANIMANAGER->findAnimation("backgroundAnimation"));

	//캐릭터
	if (_playerN == 0) { IMAGEMANAGER->findImage("crystal")->frameRender(getMemDC(), _x, _y, 0, 1); }
	else if (_playerN == 1) { IMAGEMANAGER->findImage("eyes")->frameRender(getMemDC(), _x, _y, 0, 1); }
	else if (_playerN == 2) { IMAGEMANAGER->findImage("fish")->frameRender(getMemDC(), _x, _y, 0, 1); }
	else if (_playerN == 3) { IMAGEMANAGER->findImage("melting")->frameRender(getMemDC(), _x, _y, 0, 1); }
	else if (_playerN == 4) { IMAGEMANAGER->findImage("plant")->frameRender(getMemDC(), _x, _y, 0, 1); }


	IMAGEMANAGER->findImage("txt")->render(getMemDC(), (WINSIZEX / 2) - (IMAGEMANAGER->findImage("txt")->getWidth() / 2), 0);

	IMAGEMANAGER->findImage("ly")->render(getMemDC(), 0, WINSIZEY - 400);

	//카드 추가
	for (int i = 0; i < 4; i++)
	{
		_aCard[i].img->alphaRender(getMemDC(), (WINSIZEX / 2 - 260) + 130 * i, WINSIZEY - 147, _aCard[i].alpha);

		if (PtInRect(&_aCard[i].rc, _ptMouse))
		{
			char str[256];
			HFONT myFont = CreateFont(20, 0, 0, 0, 600, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "title.otf");
			HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
			SetTextColor(getMemDC(), RGB(255, 0, 0));
			SetBkColor(getMemDC(), RGB(0, 0, 0));
			SetTextAlign(getMemDC(), TA_CENTER);
			sprintf(str, _textTitle[i]);
			TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY - 270, str, strlen(str));
			DeleteObject(myFont);

			char str1[256];
			HFONT myFont2 = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "dc.ttf");
			HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), myFont2);
			SetTextColor(getMemDC(), RGB(150, 150, 150));
			SetBkColor(getMemDC(), RGB(0, 0, 0));
			SetTextAlign(getMemDC(), TA_CENTER);
			sprintf(str1, _textDis[i]);
			TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY - 220, str1, strlen(str1));
			DeleteObject(myFont2);

		}
	}
}

void cardselectScene::setImage()
{
	IMAGEMANAGER->addFrameImage("background", "image/scene/background.bmp", 25600, 720, 20, 1, true, RGB(255, 0, 255));
	KEYANIMANAGER->addCoordinateFrameAnimation("backgroundAnimation", "background", 0, 19, 10, false, true);
	KEYANIMANAGER->start("backgroundAnimation");

	IMAGEMANAGER->addFrameImage("crystal", "image/player/crystal/crystal_hit.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eyes", "image/player/eyes/eyes_hit.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fish", "image/player/fish/fish_hit.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("melting", "image/player/melting/melting_hit.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("plant", "image/player/plant/plant_hit.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("txt", "card/cardtxt2.bmp", 432, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ly", "card/layer.bmp", 1280, 450, true, RGB(255, 0, 255));

	//카드 이미지들 추가 
	IMAGEMANAGER->addImage("BM", "card/BM.bmp", 108, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BL", "card/BL.bmp", 108, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("EE", "card/EE.bmp", 108, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("EP", "card/EP.bmp", 108, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("EF", "card/EF.bmp", 108, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HH", "card/HH.bmp", 108, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("LW", "card/LW.bmp", 108, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RC", "card/RC.bmp", 108, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RS", "card/RS.bmp", 108, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("SF", "card/SF.bmp", 108, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("SE", "card/SE.bmp", 108, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("SS", "card/SS.bmp", 108, 144, true, RGB(255, 0, 255));


}

void cardselectScene::ptInCard()
{
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&_aCard[i].rc, _ptMouse)) {
			_aCard[i].alpha = 255;
			_textTitle[i] = _text[_aCard[i].cardNum].title;
			_textDis[i] = _text[_aCard[i].cardNum].dc;
			_show = true;

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_aCard[i].cardNum == 0)
				{

				}
				else if (_aCard[i].cardNum == 1)
				{

				}
				else if (_aCard[i].cardNum == 2)
				{

				}
				else if (_aCard[i].cardNum == 3)
				{

				}
				else if (_aCard[i].cardNum == 4)
				{

				}
				else if (_aCard[i].cardNum == 5)
				{

				}
				else if (_aCard[i].cardNum == 6)
				{

				}
				else if (_aCard[i].cardNum == 7)
				{

				}
				else if (_aCard[i].cardNum == 8)
				{

				}
				else if (_aCard[i].cardNum == 9)
				{

				}
				else if (_aCard[i].cardNum == 10)
				{

				}
				else if (_aCard[i].cardNum == 11)
				{

				}
			}
		}
		else
		{
			_aCard[i].alpha = 150;
			_textTitle[i] = "";
			_textDis[i] = "";
			_show = false;
		}
	}
}

void cardselectScene::titleI()
{
	//제목

	ifstream ifile;

	ifile.open("card/title.txt");
	int i = 0;

	if (ifile.is_open())
	{
		while (i < 12)
		{
			ifile.getline(_text[i].title, sizeof(_text[i].title));
			i++;
		}
	}
	ifile.close();

}

void cardselectScene::disI()
{
	// 내용

	ifstream ifile;

	ifile.open("card/dc.txt");
	int i = 0;

	if (ifile.is_open())
	{
		while (i < 12)
		{
			ifile.getline(_text[i].dc, sizeof(_text[i].dc));
			i++;
		}
	}
	ifile.close();
}

void cardselectScene::randomCard()
{
	srand(time(NULL));

	for (int i = 0; i < 4; i++)
	{
		_a[i] = RND->getInt(12);
	}


	while (_a[0] == _a[1] || _a[0] == _a[2] || _a[0] == _a[3] || _a[1] == _a[2] || _a[1] == _a[3] || _a[2] == _a[3])
	{
		_a[0] = RND->getInt(12);
		_a[1] = RND->getInt(12);
		_a[2] = RND->getInt(12);
		_a[3] = RND->getInt(12);
	}

	for (int i = 0; i < 4; i++)
	{
		if (_a[i] == 0)
		{
			_aCard[i].img = IMAGEMANAGER->findImage("BM");
			_aCard[i].str = "BM";
			_aCard[i].cardNum = 0;
		}
		else if (_a[i] == 1)
		{
			_aCard[i].img = IMAGEMANAGER->findImage("BL");
			_aCard[i].str = "BL";
			_aCard[i].cardNum = 1;
		}
		else if (_a[i] == 2)
		{
			_aCard[i].img = IMAGEMANAGER->findImage("EE");
			_aCard[i].str = "EE";
			_aCard[i].cardNum = 2;
		}
		else if (_a[i] == 3)
		{
			_aCard[i].img = IMAGEMANAGER->findImage("EP");
			_aCard[i].str = "EP";
			_aCard[i].cardNum = 3;
		}
		else if (_a[i] == 4)
		{
			_aCard[i].img = IMAGEMANAGER->findImage("EF");
			_aCard[i].str = "EF";
			_aCard[i].cardNum = 4;
		}
		else if (_a[i] == 5)
		{
			_aCard[i].img = IMAGEMANAGER->findImage("HH");
			_aCard[i].str = "HH";
			_aCard[i].cardNum = 5;
		}
		else if (_a[i] == 6)
		{
			_aCard[i].img = IMAGEMANAGER->findImage("LW");
			_aCard[i].str = "LW";
			_aCard[i].cardNum = 6;
		}
		else if (_a[i] == 7)
		{
			_aCard[i].img = IMAGEMANAGER->findImage("RC");
			_aCard[i].str = "RC";
			_aCard[i].cardNum = 7;
		}
		else if (_a[i] == 8)
		{
			_aCard[i].img = IMAGEMANAGER->findImage("RS");
			_aCard[i].str = "RS";
			_aCard[i].cardNum = 8;
		}
		else if (_a[i] == 9)
		{
			_aCard[i].img = IMAGEMANAGER->findImage("SF");
			_aCard[i].str = "SF";
			_aCard[i].cardNum = 9;
		}
		else if (_a[i] == 10)
		{
			_aCard[i].img = IMAGEMANAGER->findImage("SE");
			_aCard[i].str = "SE";
			_aCard[i].cardNum = 10;
		}
		else if (_a[i] == 11)
		{
			_aCard[i].img = IMAGEMANAGER->findImage("SS");
			_aCard[i].str = "SS";
			_aCard[i].cardNum = 11;
		}
	}

}

void cardselectScene::move()
{
	if (_x > 600) {
		_right = false;
	}
	else if (_x < 340)
	{
		_right = true;
	}

	if (_right)
	{
		_x += 1;
		_y -= 0.5;
	}
	else
	{
		_x -= 1;
		_y += 0.5;
	}

}