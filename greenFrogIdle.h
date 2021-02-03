#pragma once
#include "greenFrogState.h"
class greenFrogIdle : public greenFrogState
{
private:
	animation* greenfrogidleright;
	animation* greenfrogidleleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

