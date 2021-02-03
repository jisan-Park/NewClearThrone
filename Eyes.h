#pragma once
#include "Player.h"
class Eyes : public Player
{
private:
	animation* eyesidleright;
	animation* eyesidleleft;
	animation* eyeswalkright;
	animation* eyeswalkleft;
	animation* eyeshitright;
	animation* eyeshitleft;
	animation* eyesdead;
	animation* eyesskill;
	animation* eyesmenuidle;
public:
	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void render(HDC hdc);
	virtual void setAnimation();
	virtual void contral();
	//==================================
	static void righthurt(void* obj);
	static void lefthurt(void* obj);
	static void makeDead(void * obj);
};

