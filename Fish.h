#pragma once
#include "Player.h"
class Fish : public Player
{
private:
	animation* fishidleright;
	animation* fishidleleft;
	animation* fishwalkright;
	animation* fishwalkleft;
	animation* fishhitright;
	animation* fishhitleft;
	animation* fishdead;
	animation* fishmenuidle;
public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);
	virtual void setAnimation();
	virtual void contral();

	static void righthurt(void* obj);
	static void lefthurt(void* obj);
	static void makeDead(void * obj);
};

