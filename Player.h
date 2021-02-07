#pragma once
#include "singletonBase.h"
#include "assultRifle.h"
#include "grenadeLauncher.h"
#include "machineGun.h"
#include "pistol.h"
#include "razerRifle.h"
#include "shotGun.h"
#include "shovel.h"
#include "sword.h"
#include "triplemachinegun.h"

enum MOVEDIRCTION
{
	NOMOVE,
	RIGHTMOVE,
	LEFTMOVE,
	UPMOVE,
	DOWNMOVE
};

enum DIRECTION
{
	RIGHT,
	LEFT
};

enum PLAYERSTATE
{
	IDLE,
	WALK,
	HURT,
	DEAD,
	SKILL
};

class Player
{
protected:
	POINT _pt;				//xy ��ǥ�Դϴ�
	float _width, _height;	//�ʺ� �����Դϴ�
	RECT _rc;				//�浹������ ��Ʈ�Դϴ�
	int _speed;				//�����̴� �ӵ��Դϴ�
	int _damage;			//�������Դϴ�
	int _firecnt;			//�߻� ���Դϴ�
	float _aimAngle;		//���ذ��Դϴ�
	float _moveAngle;		//�̵����Դϴ�
	image* _img;			//�̹��� �Դϴ�
	animation* _motion;		//�ִϸ��̼� ���
	bool _ishit;			//�Ȱ�Ȯ��
	int _maxhp;				//��HP
	int _hp;				//HP
	bool _isdead;			//�״� ����
	int _playerbullet;		//���� �Ѿ� ����
	int _playerbulletMax;	//�ִ� �Ѿ� ����
	int _playershellb;
	int _playershellbMax;
	int _playerenergyb;
	int _playerenergubMax;
	int _playerexplodeb;
	int _playerecplodbeMax;
	int _angleCard = 0;
	bool _weaponReady;
	bool _assfire;
	bool _shotfire;
	int _interval = 10;
	int _count;


	//���� �Լ�
	bool _isBloodLust;
	bool _isRecycleGland;
	bool _isStrongSpirit;



	//=========================================
	bool _isdash;//fish ��ų Ʈ����
	float _pushp;//fish ��ų �̴� ��
	//=========================================
	PLAYERSTATE _playerstate;
	DIRECTION _direction;
	MOVEDIRCTION _movedirctionx;
	MOVEDIRCTION _movedirctiony;

	weapon* _currentWeapon;
	weapon* _readyWeapon;
public:
	Player();
	~Player();

	virtual HRESULT init(float x, float y);
	virtual void update();
	virtual void release();

	virtual void render(HDC hdc);

	virtual void attack();
	virtual void move();
	virtual void setAnimation();
	virtual void playerWeaponSwap();
	virtual void groundWeaponSwap(weaponType type);
	virtual void groundWeaponGet(weaponType type);

	virtual void BackMuscle();		//ź�� ������ �ִ�ġ ����
	virtual void Bloodlust();		//�� ���߽� 1/13(Ȯ���� �ٲ㵵 �ɵ�) �� ��1 ä����
	virtual void EagleEyes();		//ź ��Ȯ�� ���� ( ��ź�ѵ� ��ź �پ��)
	virtual void ExtraFeet();		//�̵��ӵ� ����
	virtual void LastWish();		//ü�� Ǯ�� ä���ְ� ź�� ������ ä����
	virtual void RecycleGland();	//�� ���߽� 60% Ȯ���� ź�� ȸ���� (1�ٴ� ����� 1��ŭ 5�ٴ� ����� 5��ŭ)
	virtual void Rhinoskin();		//�� �ִ�ġ 4 ����, �� 4 ä����
	virtual void Stress();			//�ǰ� �������� �Ѿ˼ӵ� ������
	virtual void Strongspirit();	//Ȱ��ȭ�� �Ӹ����� �� ����� << �Ȼ��ܵ� �ɵ� 5�ʵ��� Ʈ���� ��1�� ����


	virtual void Bloodlustupdate();
	virtual void RecycleGlandate();

	virtual void collision();

	//�ݹ��� ���� ����,����
	//=========================================
	DIRECTION getDirection() { return _direction; }
	void setDirection(DIRECTION direction) { _direction = direction; }

	PLAYERSTATE getState() { return _playerstate; }
	void setState(PLAYERSTATE state) { _playerstate = state; }

	image* getImage() { return _img; }
	void setImage(image* img) { _img = img; }

	animation* getMotion() { return _motion; }
	void setteMotion(animation* ani) { _motion = ani; }

	void setIshit(bool ishit) { _ishit = ishit; }

	void setIsdead(bool isdead) { _isdead = isdead; }
	//=========================================
	POINT getPt() { return _pt; }
	void setPT(POINT pt) { _pt = pt; }

	RECT getRect() { return _rc; };

	//int getPlayerbullet() { return _playerbullet; }
	//void setPlayerbullet(int playerbullet) { _playerbullet = playerbullet; }

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }

	int getInterval() { return _interval; }

	int getMaxhp() { return _maxhp; }
	void setMaxhp(int maxhp) { _maxhp = maxhp; }

	void setWeaponReady(bool ready) { _weaponReady = ready; }

	int getAngleCard() { return _angleCard; }

	int getPlayerbullet() { return _playerbullet; }
	void setPlayerbullet(int playerbullet) { _playerbullet = playerbullet; }

	int getPlayershellb() { return _playershellb; }
	void setPlayershellb(int playershellb) { _playershellb = playershellb; }

	int getPlayerenergyb() { return _playerenergyb; }
	void setPlayerenergyb(int playerenergyb) { _playerenergyb = playerenergyb; }

	int getPlayerexplodeb() { return _playerexplodeb; }
	void setPlayerexplodeb(int playerexplodeb) { _playerexplodeb = playerexplodeb; }

	weapon* getWeapon() { return _currentWeapon; }

};
