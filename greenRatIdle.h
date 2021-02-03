#pragma once
#include "greenRatState.h"
class greenRatIdle : public greenRatState
{
private:
	animation* greenratidleright;
	animation* greenratidleleft;

public:
	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
};

