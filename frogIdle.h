#pragma once
#include "frogState.h"
class frogIdle : public frogState
{
private:
	animation* frogidleright;
	animation* frogidleleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

