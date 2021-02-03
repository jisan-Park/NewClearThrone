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
	E_HURT,
	E_DEAD,
	E_ATTACK,
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
	int speed;				//움직이는 속도입니다
	int damage;			//데미지입니다
	int firecnt;			//발사 쿨입니다
	float aimAngle;		//조준각입니다
	float moveAngle;		//이동각입니다
	bool isHurt;		//다쳤는지 보는겁니다


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
	static void hurtFinish(void* obj);
	virtual void setRect();
};

