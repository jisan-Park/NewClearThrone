#include "stdafx.h"
#include "bigDogSpin.h"

HRESULT bigDogSpin::init(enemyinfo info)
{
	bigdogspin = new animation;
	bigdogspin->init("bigdog_spin");
	bigdogspin->setPlayFrame(0, 2, false, true);
	bigdogspin->setFPS(10);

	bigdogspinendright = new animation;
	bigdogspinendright->init("bigdog_spinend");
	bigdogspinendright->setPlayFrame(0, 1, false, false, spinend, this);
	bigdogspinendright->setFPS(10);

	bigdogspinendleft = new animation;
	bigdogspinendleft->init("bigdog_spinend");
	bigdogspinendleft->setPlayFrame(3, 2, false, false, spinend, this);
	bigdogspinendleft->setFPS(10);

	bigdogspinhurt = new animation;
	bigdogspinhurt->init("bigdog_spin_hurt");
	bigdogspinhurt->setPlayFrame(0, 1, false, false, hurtFinish, this);
	bigdogspinhurt->setFPS(10);

	_dogangle = 0;
	_img = IMAGEMANAGER->findImage("bigdog_spin");
	_motion = bigdogspin;
	_motion->start();
	_pt = info.pt;
	return S_OK;
}

void bigDogSpin::update(enemyinfo & info)
{
	if (_spinend == true) info.nextState = E_IDLE;
	if (info.isHurt == true)
	{
		isHurt = true;
		info.isHurt = false;
	}
	_pt = info.pt;
	_dogangle += 0.05f;
	_spincnt++;
	if (_spincnt < 300)
	{
		if (_spincnt % 10 == 0)
		{
			SOUNDMANAGER->play("ºòµ¶ÃÑ½î´Â", GAMEMANAGER->getSfxVolume() * GAMEMANAGER->getMasterVolume());
			for (int i = 0; i < 4; i++)
			{
				BULLETMANAGER->EnemyFire(E_ANGLE16_1, _pt, 3, PI / 2 * i + _dogangle, 2);
			}
		}
	}
	if (_spincnt >= 300)
	{
		if (info.direction == LEFT) _motion = bigdogspinendleft;
		if (info.direction == RIGHT) _motion = bigdogspinendright;
	}
	if (_motion != bigdogspinendleft && _motion != bigdogspinendright)
	{
		if (isHurt == true)
		{
			_img = IMAGEMANAGER->findImage("bigdog_spin_hurt");
			if (info.direction == E_LEFT) _motion = bigdogspinhurt;
			if (info.direction == E_RIGHT) _motion = bigdogspinhurt;
		}
		else
		{
			if (!MAPMANAGER->isCollisionTile(info.pt, info.width, info.height)) {
				info.pt.x += cosf(info.moveAngle)* info.speed;
				info.pt.y += -sinf(info.moveAngle)* info.speed;
			}
			_img = IMAGEMANAGER->findImage("bigdog_spin");
			{
				_motion = bigdogspin;
			}

			if (_spincnt > 300)
			{
				_img = IMAGEMANAGER->findImage("bigdog_spinend");
				if (info.direction == E_LEFT) _motion = bigdogspinendleft;
				if (info.direction == E_RIGHT) _motion = bigdogspinendright;
			}
		}
	}
	if (_motion->isPlay() == false) _motion->start();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void bigDogSpin::spinend(void * obj)
{
	bigDogSpin*e = (bigDogSpin*)obj;
	e->setSpinend(true);
}
