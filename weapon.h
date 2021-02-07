#pragma once
#include "bullet16.h"
#include "bullet1.h"
#include "enemyBullet16_1.h"
#include "enemyBullet16_2.h"
#include "enemyShotGun.h"

enum weaponState
{
	ONGROUND,
	NOWUSING,
	READYTOUSE
};

enum weaponType
{
	ASSULTRIFLE,
	GRENADELAUNCHER,
	MACHINEGUN,
	PISTOL,
	RAZERRIFLE,
	SHOTGUN,
	SHOVEL,
	SWORD,
	TRIPLEMACHINEGUN,
	WRENCH,
};
class weapon
{
protected:
	image* _img;		// �̹����Դϴ�
	POINT _pt;			// ��ǥ�Դϴ�
	float _imgx, _imgy;	// �̹��� �Ѹ� ��ǥ(�������ư�����)
	weaponState _state;	// �����Դϴ�
	weaponType _type;	// ����Ÿ���Դϴ�
	RECT _rc;
	float _bulletSpd;
	float _radius;	// �̹��� 
	float _angle;		// ���ذ����Դϴ�
	float _rndSpreadAngle = 0.1f;
	float _meleeAngle = PI / 2;	// �������� ���� �� �� �����Դϴ�
	int _index;			// ���� ���� �����Ǵ� �������ε����Դϴ�
	int _damage;		// �������Դϴ�
	int _coolDown;		// ����ӵ�(�������� ����)
	int _coolCnt;		// ����Ÿ�̸�
	float _range;		// ���������� �� �ĸ��� �����Դϴ�

public:
	weapon() {};
	~weapon() {};
	virtual HRESULT init(POINT pt, weaponState state);
	virtual void update();
	virtual void fire();
	void release();
	virtual void render(HDC hdc);
	void setFrameIndex(float angle);
	void setFrameIndex8(float angle);
	void setAngle(float angle);
	image* getImg() { return _img; };
	void Position();
	void setPt(POINT pt) { _pt = pt; };
	weaponType getType() { return _type; };
	POINT getPt() { return _pt; };
};

