#pragma once
#include "Player.h"
class Plant : public Player
{
private:
	animation* plantidleright;
	animation* plantidlelft;
	animation* plantwalkright;
	animation* plantwalkleft;
	animation* planthitright;
	animation* planthitleft;
	animation* plantdead;
	animation* plantskill;
	animation* plantmenuidle;
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

