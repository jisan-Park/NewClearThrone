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
	image* _img;		// 이미지입니다
	POINT _pt;			// 좌표입니다
	float _imgx, _imgy;	// 이미지 뿌릴 좌표(빙빙돌아갈거임)
	weaponState _state;	// 상태입니다
	weaponType _type;	// 무기타입입니다
	RECT _rc;
	float _bulletSpd;
	float _radius;	// 이미지 
	float _angle;		// 조준각도입니다
	float _rndSpreadAngle = 0.1f;
	float _meleeAngle = PI / 2;	// 근접무기 보정 해 줄 각도입니다
	int _index;			// 각도 따라서 지정되는 프레임인덱스입니다
	int _damage;		// 데미지입니다
	int _coolDown;		// 연사속도(낮을수록 빠름)
	int _coolCnt;		// 연사타이머
	float _range;		// 근접무기일 때 후리는 범위입니다

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

