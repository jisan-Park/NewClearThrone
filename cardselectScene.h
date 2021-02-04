#pragma once
#include "gameNode.h"
#include <fstream>
#include <string.h> 

struct tagCard
{
	int cardNum;
	image *img;
	RECT rc;
	int alpha;
	const char* str;
};

struct tagText
{
	char title[100];
	char dc[200];
};

class cardselectScene : public gameNode
{
private:
	float _x;
	float _y;
	bool _right;

	//rand
	int _a[4];
	tagCard _aCard[4];

	//플레이어 
	int _playerN;

	//excel
	const char* _textDis[4];
	const char* _textTitle[4];
	tagText _text[12];
	bool _show;
public:
	cardselectScene();
	~cardselectScene();

	HRESULT init();
	void update();
	void release();
	void render();

	void setImage();
	void ptInCard();
	void titleI();
	void disI();
	void randomCard();
	void move();

	//
	void playerNum(int num) { _playerN = num; };


	//
	int getCardNum(int n) { return _aCard[n].cardNum; };

};