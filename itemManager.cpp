#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init()
{
	setimage();
	setItembox();
	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{
	collsion();
	for (_viItembox = _vItembox.begin(); _viItembox != _vItembox.end(); _viItembox++)
	{
		(*_viItembox)->update();
	}
	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end(); _viWeapon++)
	{
		(*_viWeapon)->update();
	}
}

void itemManager::render(HDC hdc)
{
	for (_viItembox = _vItembox.begin(); _viItembox != _vItembox.end(); _viItembox++)
	{
		(*_viItembox)->render(hdc);

	}
	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end(); _viWeapon++)
	{
		(*_viWeapon)->render(hdc);
	}
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		(*_viItem)->render(hdc);
	}
}

void itemManager::setimage()
{
	IMAGEMANAGER->addFrameImage("bullet_box", "image/item/bullet_box.bmp", 256, 30, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("weapon_box", "image/item/weapon_box.bmp", 256, 30, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("medkit_box", "image/item/medkit_box.bmp", 256, 30, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bullet_item", "image/item/bullet_item.bmp", 140, 20, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("medkit_item", "image/item/medkit_item.bmp", 140, 20, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rad_canister", "image/item/rad_canister.bmp", 139, 32, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rad_canister_hurt", "image/item/rad_canister_hurt.bmp", 60, 32, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rad_canister_dead", "image/item/rad_canister_dead.bmp", 60, 32, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rad", "image/item/rad.bmp", 112, 8, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigrad", "image/item/bigrad.bmp", 168, 20, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("maggot_canister", "image/item/maggot_canister.bmp", 396, 44, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("maggot_canister_hurt", "image/item/maggot_canister_hurt.bmp", 124, 44, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("maggot_canister_dead", "image/item/maggot_canister_dead.bmp", 144, 38, 4, 1, true, RGB(255, 0, 255));
}

void itemManager::setItembox()
{
	for (int i = 0; i < 3; i++)
	{
		itemBox* temp;
		temp = new bulletBox;
		temp->init(500 * (i + 1), 500);
		_vItembox.push_back(temp);
	}
	for (int i = 0; i < 3; i++)
	{
		itemBox* temp1;
		temp1 = new weaponBox;
		temp1->init(500 * (i + 1), 700);
		_vItembox.push_back(temp1);
	}
	for (int i = 0; i < 3; i++)
	{
		itemBox* temp2;
		temp2 = new medkitBox;
		temp2->init(500 * (i + 1), 800);
		_vItembox.push_back(temp2);
	}
}

void itemManager::collsion()
{
	for (int i = 0; i < _vItembox.size(); i++)
	{
		RECT temp3;
		if (_vItembox[i]->getIsopen()) {
			continue;
		}
		if (IntersectRect(&temp3, &PLAYERMANAGER->getPlayer()->getRect(), &_vItembox[i]->getItemboxRc()))
		{
			_vItembox[i]->setIsopen(true);
			if (_vItembox[i]->getBoxtype() == WEAPONBOX)
			{
				createWeapon(_vItembox[i]->getItemPt());
			}
			if(_vItembox[i]->getBoxtype() == BULLETBOX)
			{
				item* temp;
				temp = new bulletitem;
				temp->init(_vItembox[i]->getItemPt().x, _vItembox[i]->getItemPt().y);
				_vItem.push_back(temp);
			}
			if (_vItembox[i]->getBoxtype() == MEDKITBOX)
			{
				item* temp1;
				temp1 = new medkititem;
				temp1->init(_vItembox[i]->getItemPt().x, _vItembox[i]->getItemPt().y);
				_vItem.push_back(temp1);
			}
			break;

		}

	}
	
	for (int i = 0; i < _vItem.size(); i++)
	{		
		RECT temp3;
		if (IntersectRect(&temp3, &PLAYERMANAGER->getPlayer()->getRect(), &_vItem[i]->getItemRc()))
		{
			if (_vItem[i]->getItemtype() == BULLETITEM)
			{
				PLAYERMANAGER->getPlayer()->setPlayerbullet(PLAYERMANAGER->getPlayer()->getPlayerbullet() + 30);
				
			}
			if (_vItem[i]->getItemtype() == MEDKETITEM && PLAYERMANAGER->getPlayer()->getHp() < PLAYERMANAGER->getPlayer()->getMaxhp())
			{
				PLAYERMANAGER->getPlayer()->setHp(PLAYERMANAGER->getPlayer()->getHp() + 2);
			}
			_vItem.erase(_vItem.begin() + i);
			break;
		}
		

	}
}

void itemManager::createWeapon(POINT pt)
{
	//random
	//_weaponType = (weaponType)(int)RND->getFromIntTo(0, 9);
	_weaponType = PISTOL;
	switch (_weaponType)
	{
	case ASSULTRIFLE:
		break;
	case GRENADELAUNCHER:
		break;
	case MACHINEGUN:
		break;
	case PISTOL:
		weapon* temp;
		temp = new pistol;
		temp->init(pt, ONGROUND);
		_vWeapon.push_back(temp);
		break;
	case RAZERRIFLE:
		break;
	case SHOTGUN:
		break;
	case SHOVEL:
		break;
	case SWORD:
		break;
	case TRIPLEMACHINEGUN:
		break;
	case WRENCH:
		break;
	default:
		break;
	}
}
