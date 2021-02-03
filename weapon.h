#pragma once

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
	weaponState _state;	// 상태입니다
	weaponType _type;	// 무기타입입니다
	float _hwidth, _hheight; // 이미지 밀어주는 값입니당
	float _angle;		// 조준각도입니다
	float _meleeAngle;	// 근접무기 보정 해 줄 각도입니다
	int _index;			// 각도 따라서 지정되는 프레임인덱스입니다
	int _damage;		// 데미지입니다
	int _coolDown;		// 연사속도(낮을수록 빠름)
	float _range;		// 근접무기일 때 후리는 범위입니다

public:
	weapon() {};
	~weapon() {};
	virtual HRESULT init(POINT pt);
	virtual void update();
	void release();
	void render(HDC hdc);
	void setFrameIndex(float angle);
	void setAngle(float angle);
	void setWH();
	image* getImg() { return _img; };
};

