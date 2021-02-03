#pragma once
#include "Player.h"
class Meiting : public Player
{
private:
	animation* meltingidleright;
	animation* meltingidleleft;
	animation* meltingwalkright;
	animation* meltingwalkleft;
	animation* meltinghitright;
	animation* meltinghitleft;
	animation* meltingdead;
	animation* meltingmenuidle;
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

