#pragma once
enum ENEMYDIRECTION
{
	E_RIGHT,
	E_LEFT
};

enum ENEMYSTATE
{
	E_IDLE,
	E_WALK,
	E_FIRE,
	E_DEAD,
	E_ATTACK,
	E_BURROW,
	E_APPEAR,

	E_IMMUNE
};
enum ENEMYNOTICESTATE
{
	UNNOTICED,
	NOTICED
};

enum ENEMYMOVETYPE
{
	ALWAYSFOLLOW,
	BALANCE,
	ALWAYSRUN
};

struct enemyinfo
{
	POINT pt;				//xy 좌표입니다
	float width, height;	//너비 높이입니다
	RECT rc;				//충돌판정용 렉트입니다
	int hp;				//hp입니다.
	int originSpeed;		// 플랜트 스킬에 갇혔을때 돌아오게 할 스피드입니다 시팔,,
	int speed;				//움직이는 속도입니다
	int damage;			//데미지입니다
	int firecnt;			//발사 쿨입니다
	float aimAngle;		//조준각입니다
	float moveAngle;		//이동각입니다
	float noticeRange;
	bool isHurt;		//다쳤는지 보는겁니다
	bool isFire;		//fire했는지 보는겁니다

	ENEMYSTATE state;
	ENEMYSTATE nextState;

	ENEMYMOVETYPE movetype;
	ENEMYDIRECTION direction;
	ENEMYNOTICESTATE nstate;
};

class enemyState
{
protected:
	//이미지
	image* _img;
	//사용될 애니메이션 변수들 얼마든지 추가되도 상관없음
	animation* _motion;
	POINT _pt;

	bool isHurt;
	bool isFire;		//fire했는지 보는겁니다

public:
	enemyState();
	~enemyState();

	virtual HRESULT init(enemyinfo info);
	virtual void update(enemyinfo &info);
	virtual void release();
	virtual void render(HDC hdc);
	void init(image* img, animation* ani, int x, int y);

	void setImage(image* temp) { _img = temp; };
	void setAnimation(animation* ani) { _motion = ani; };
	void setPoint(int x, int y) { _pt.x = x; _pt.y = y; };
	void setHurt(bool what) { isHurt = what; };
	void setFire(bool b) { isFire = b; };
	static void hurtFinish(void* obj);
	static void fireFinish(void * obj);
	virtual void setRect();
};

