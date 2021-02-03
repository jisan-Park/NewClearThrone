#include "stdafx.h"
#include "weapon.h"

HRESULT weapon::init(POINT pt)
{
	return S_OK;
}

void weapon::update()
{
}

void weapon::release()
{
}

void weapon::render(HDC hdc)
{
	_img->frameRender(hdc, _pt.x - _hwidth, _pt.y - _hwidth, _index, 0);
}

void weapon::setFrameIndex(float angle)
{
	//float imageangle;
	//angle = _angle + PI16;
	//_index = int(angle / PI8);
	//_img->setFrameX(_index);
	if ((_angle < PI16 * 1 && _angle >= 0) || (_angle > PI - PI16 && _angle < PI*2)) _index = 0;
	if (_angle > PI16 * 1 && _angle <= PI16 * 3) _index = 1;
	if (_angle > PI16 * 3 && _angle <= PI16 * 5) _index = 2;
	if (_angle > PI16 * 5 && _angle <= PI16 * 7) _index = 3;
	if (_angle > PI16 * 7 && _angle <= PI16 * 9) _index = 4;
	if (_angle > PI16 * 9 && _angle <= PI16 * 11) _index = 5;
	if (_angle > PI16 * 11 && _angle <= PI16 * 13) _index = 6;
	if (_angle > PI16 * 13 && _angle <= PI16 * 15) _index = 7;
	if (_angle > PI16 * 15 && _angle <= PI16 * 17) _index = 8;
	if (_angle > PI16 * 17 && _angle <= PI16 * 19) _index = 9;
	if (_angle > PI16 * 19 && _angle <= PI16 * 21) _index = 10;
	if (_angle > PI16 * 21 && _angle <= PI16 * 23) _index = 11;
	if (_angle > PI16 * 23 && _angle <= PI16 * 25) _index = 12;
	if (_angle > PI16 * 25 && _angle <= PI16 * 27) _index = 13;
	if (_angle > PI16 * 27 && _angle <= PI16 * 29) _index = 14;
	if (_angle > PI16 * 29 && _angle <= PI16 * 31) _index = 15;


}

void weapon::setAngle(float angle)
{
	switch (_type)
	{
	case ASSULTRIFLE:	case GRENADELAUNCHER:	case MACHINEGUN:
	case PISTOL:		case RAZERRIFLE:		case SHOTGUN:
	case TRIPLEMACHINEGUN:
		_angle = angle;
		break;
	case SHOVEL:		case SWORD:				case WRENCH:
		_angle = angle - _meleeAngle;
		break;
	default:
		break;
	}
	if (_angle >= PI2) _angle -= PI2;
	if (_angle <= 0) _angle += PI2;
}

void weapon::setWH()
{
	_hwidth = getImg()->getFrameWidth() / 2;
	_hheight = getImg()->getFrameHeight() / 2;
}
