#pragma once
#include <vector>
//struct tagBullet
//{
//	image* img;				//�Ѿ��� �̹���
//	RECT rc;
//	POINT pt;				//���� ��ǥ
//	POINT firept;			//�߻��� �� ��ǥ
//	whoshot who;
//	float angle;			//����
//	float radius;			//������
//	float speed;			//���ǵ�
//	bool isFire;			//�߻��ߴ�?
//	int count;				//������ �̹��� ī��Ʈ��
//	int damage;
//};
class bullet
{
protected:

	//tagBullet _bullet;
	image* _img;				//�Ѿ��� �̹���
	RECT _rc;
	POINT _pt;				//���� ��ǥ
	POINT _firept;			//�߻��� �� ��ǥ
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
	virtual void move();

	RECT getRect() { return _rc; }
	float getAngle() { return _angle; }
	int getDamage() { return _damage; }
	bool getGone() { return _gone; }
	POINT getPt() { return _pt; }

};

