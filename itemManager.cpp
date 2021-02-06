#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init()
{
	setimage();
	
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

void itemManager::weaponSwap()
{
	for (int i = 0; i < _vWeapon.size(); i++)
	{
		RECT temp4;
		RECT tempWrc = RectMakeCenter(_vWeapon[i]->getPt().x, _vWeapon[i]->getPt().y, 40, 40);
		if (IntersectRect(&temp4, &PLAYERMANAGER->getPlayer()->getRect(), &tempWrc))
		{
			weaponType temptype;
			temptype = PLAYERMANAGER->getPlayer()->getWeapon()->getType();
			PLAYERMANAGER->getPlayer()->groundWeaponSwap(_vWeapon[i]->getType());
			_vWeapon.erase(_vWeapon.begin() + i);
			switch (temptype)
			{
			case ASSULTRIFLE:
			{
				weapon* tempWp;
				tempWp = new assultRifle;
				tempWp->init(PLAYERMANAGER->getPlayer()->getPt(), ONGROUND);
				_vWeapon.push_back(tempWp);
			}
			break;
			case GRENADELAUNCHER:
			{
				weapon* tempWp;
				tempWp = new grenadeLauncher;
				tempWp->init(PLAYERMANAGER->getPlayer()->getPt(), ONGROUND);
				_vWeapon.push_back(tempWp);
			}
			break;
			case MACHINEGUN:
			{
				weapon* tempWp;
				tempWp = new machineGun;
				tempWp->init(PLAYERMANAGER->getPlayer()->getPt(), ONGROUND);
				_vWeapon.push_back(tempWp);
			}
			break;
			case PISTOL:
			{
				weapon* tempWp;
				tempWp = new pistol;
				tempWp->init(PLAYERMANAGER->getPlayer()->getPt(), ONGROUND);
				_vWeapon.push_back(tempWp);
			}
			break;
			case RAZERRIFLE:
			{
				weapon* tempWp;
				tempWp = new razerRifle;
				tempWp->init(PLAYERMANAGER->getPlayer()->getPt(), ONGROUND);
				_vWeapon.push_back(tempWp);
			}
			break;
			case SHOTGUN:
			{
				weapon* tempWp;
				tempWp = new shotGun;
				tempWp->init(PLAYERMANAGER->getPlayer()->getPt(), ONGROUND);
				_vWeapon.push_back(tempWp);
			}
			break;
			case SHOVEL:
			{
				weapon* tempWp;
				tempWp = new shovel;
				tempWp->init(PLAYERMANAGER->getPlayer()->getPt(), ONGROUND);
				_vWeapon.push_back(tempWp);
			}
			break;
			case SWORD:
			{
				weapon* tempWp;
				tempWp = new sword;
				tempWp->init(PLAYERMANAGER->getPlayer()->getPt(), ONGROUND);
				_vWeapon.push_back(tempWp);
			}
			break;
			case TRIPLEMACHINEGUN:
			{
				weapon* tempWp;
				tempWp = new triplemachinegun;
				tempWp->init(PLAYERMANAGER->getPlayer()->getPt(), ONGROUND);
				_vWeapon.push_back(tempWp);
			}
			break;
			case WRENCH:
			{
				weapon* tempWp;
				tempWp = new wrench;
				tempWp->init(PLAYERMANAGER->getPlayer()->getPt(), ONGROUND);
				_vWeapon.push_back(tempWp);
			}
			break;
			default:
				break;
			}

		}
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

void itemManager::setItembox(ITEMBOXTYPE itemboxtype, POINT PT)
{
	_itemboxtype = itemboxtype;

	switch (_itemboxtype)
	{
	case BULLETITEMBOX:
	{
		itemBox* temp;
		temp = new bulletBox;
		temp->init(PT.x, PT.y);
		_vItembox.push_back(temp);
	}
	break;
	case WEAPOMITEMBOX:
	{
		itemBox* temp1;
		temp1 = new weaponBox;
		temp1->init(PT.x, PT.y);
		_vItembox.push_back(temp1);
	}
	break;
	case MEDKITITEMBOX:
	{
		itemBox* temp2;
		temp2 = new medkitBox;
		temp2->init(PT.x, PT.y);
		_vItembox.push_back(temp2);
	}
	break;
	default:
		break;
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
			if (_vItembox[i]->getBoxtype() == BULLETBOX)
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
	_weaponType = (weaponType)(int)RND->getFromIntTo(0, 9);
	//_weaponType = PISTOL;
	switch (_weaponType)
	{
	case ASSULTRIFLE:
	{
		weapon* tempwp2;
		tempwp2 = new assultRifle;
		tempwp2->init(pt, ONGROUND);
		_vWeapon.push_back(tempwp2);
	}
		break;
	case GRENADELAUNCHER:
	{
		weapon* tempwp2;
		tempwp2 = new grenadeLauncher;
		tempwp2->init(pt, ONGROUND);
		_vWeapon.push_back(tempwp2);
	}
		break;
	case MACHINEGUN:
	{
		weapon* tempwp2;
		tempwp2 = new machineGun;
		tempwp2->init(pt, ONGROUND);
		_vWeapon.push_back(tempwp2); 
	}
		break;
	case PISTOL:
	{
		weapon* tempwp2;
		tempwp2 = new pistol;
		tempwp2->init(pt, ONGROUND);
		_vWeapon.push_back(tempwp2);
	}
		break;
	case RAZERRIFLE:
	{
		weapon* tempwp2;
		tempwp2 = new razerRifle;
		tempwp2->init(pt, ONGROUND);
		_vWeapon.push_back(tempwp2);
	}
		break;
	case SHOTGUN:
	{
		weapon* tempwp2;
		tempwp2 = new shotGun;
		tempwp2->init(pt, ONGROUND);
		_vWeapon.push_back(tempwp2);
	}
		break;
	case SHOVEL:
	{
		weapon* tempwp2;
		tempwp2 = new pistol;
		tempwp2->init(pt, ONGROUND);
		_vWeapon.push_back(tempwp2);
	}
		break;
	case SWORD:
	{
		weapon* tempwp2;
		tempwp2 = new sword;
		tempwp2->init(pt, ONGROUND);
		_vWeapon.push_back(tempwp2);
	}
		break;
	case TRIPLEMACHINEGUN:
	{
		weapon* tempwp2;
		tempwp2 = new triplemachinegun;
		tempwp2->init(pt, ONGROUND);
		_vWeapon.push_back(tempwp2);
	}
		break;
	case WRENCH:
	{
		weapon* tempwp2;
		tempwp2 = new wrench;
		tempwp2->init(pt, ONGROUND);
		_vWeapon.push_back(tempwp2);
	}
		break;
	default:
		break;
	}
}
