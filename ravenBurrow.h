#pragma once
#include "ravenState.h"
class ravenBurrow : public ravenState
{
private:
	animation*	ravenflyright;
	animation*	ravenflyleft;

	animation*	ravenliftright;
	animation*	ravenliftleft;


public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
	static void immune(void* obj);
	static void immune2(void* obj);

	image* getImage() { return _img; }
	void setImage(image* img) { _img = img; }

	animation* getMotion() { return _motion; }
	void setteMotion(animation* ani) { _motion = ani; }
};

