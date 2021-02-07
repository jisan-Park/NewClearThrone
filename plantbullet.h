#pragma once
#include "singletonBase.h"

class plantbullet : public singletonBase <plantbullet>
{
private:
	image* _img;				//�Ѿ��� �̹���
	RECT _rc;
	POINT _pt;				//���� ��ǥ
	POINT _firept;			//�߻��� �� ��ǥ
	float _angle;			//����
	float _radius;			//������
	float _speed;			//���ǵ�
	bool _isFire;			//�߻��ߴ�?
	int _count;				//������ �̹��� ī��Ʈ��
	float _range;			//��Ÿ�
	int _bulletmax;
	animation* _motion;
	animation* _plantbullet;
	bool _ison;

public:
	plantbullet() {};
	~plantbullet() {};

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void fire(POINT pt, float speed, float angle);
	virtual void move();
	virtual void setAni();
	
	void collision();
	bool getIsfire() { return _isFire; }
	void setISfire(bool isfire) { _isFire = isfire; };
	RECT getRC() { return _rc; }
	image* getImage() { return _img; }
	void setImage(image* img) { _img = img; };
	void setMotion();
};


