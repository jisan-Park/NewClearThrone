#pragma once
#include "Player.h"
class Crystal : public Player
{
private:
	animation* crystalidleright;
	animation* crystalidleleft;
	animation* crystalwalkright;
	animation* crystalwalkleft;
	animation* crystalhitright;
	animation* crystalhitleft;
	animation* crystaldead;
	animation* crystalskill;
	animation* crystalmenuidle;
public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);
	virtual void setAnimation();
	virtual void contral();
	//==================================
	static void righthurt(void* obj);
	static void lefthurt(void* obj);
	static void skillback(void* obj);
	static void makeDead(void * obj);
};

