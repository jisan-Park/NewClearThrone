#pragma once
#include "gatorState.h"
class gatorIdle : public gatorState
{
private:
	animation* gatoridleleft;
	animation* gatoridleright;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

