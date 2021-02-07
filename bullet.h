#pragma once
#include <vector>
enum BULLETTYPE
{
	ANGLE16,
	ANGLE1,
	FLAME,
	GRENADE,
	SHOTGUNBULLET,
	LASERBULLET,

	E_ANGLE16_1,
	E_ANGLE16_2,
	E_SHOTGUN,
	E_SHOTGUN2

};
class bullet
{
protected:

	//tagBullet _bullet;
	image* _img;				//�Ѿ��� �̹���
	RECT _rc;
	POINT _pt;				//���� ��ǥ
	POINT _firept;			//�߻��� �� ��ǥ

	BULLETTYPE _type;
	float _angle;			//����
	float _radius;			//������
	float _speed;			//���ǵ�
	bool _isFire;			//�߻��ߴ�?
	int _count;				//������ �̹��� ī��Ʈ��
	int _damage;
	float _range;			//��Ÿ�

	bool _gone;
public:
	bullet() {};
	~bullet() {};

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void fire(POINT pt, float speed, float angle, int damage);
	void setFrameIndex8();
	virtual void move();
	virtual void explode();

	RECT getRect() { return _rc; }
	float getAngle() { return _angle; }
	int getDamage() { return _damage; }
	bool getGone() { return _gone; }
	POINT getPt() { return _pt; }
	float getSpeed() { return _speed; }
	BULLETTYPE getType() { return _type; }
};

