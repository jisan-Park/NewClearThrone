#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;


	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		SOUNDMANAGER->init();
		KEYANIMANAGER->init();
		INIDATA->init();
		GAMEMANAGER->init();
		MAPMANAGER->init();
		CAMERAMANAGER->init();
		PLAYERMANAGER->setimage();
		ENEMYMANAGER->init();
		WEAPONMANAGER->init();
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		//KillTimer(_hWnd, 1);

		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();
		INIDATA->releaseSingleton();
		GAMEMANAGER->release();
		GAMEMANAGER->releaseSingleton();
		MAPMANAGER->release();
		MAPMANAGER->releaseSingleton();
		PLAYERMANAGER->release();
		PLAYERMANAGER->releaseSingleton();
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();
		ENEMYMANAGER->release();
		ENEMYMANAGER->releaseSingleton();
		WEAPONMANAGER->release();
		WEAPONMANAGER->releaseSingleton();
	}
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	SOUNDMANAGER->update();

}

void gameNode::render()
{

}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	PAINTSTRUCT ps;
	HDC			hdc;	//<-- æÍ ¡¯¬• ¡ﬂø‰«‘

	switch (iMessage)
	{
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));	
		break;
		case WM_KEYDOWN:
			switch (wParam)
			{

				case VK_ESCAPE:
					PostQuitMessage(0);
				break;
			}
		break;
		case WM_MOUSEWHEEL:
		{
			short delta = HIWORD(wParam);

			delta = (delta / WHEEL_DELTA); // WHEEL_DELTA : 120
			//»Ÿ ø√∏∞∞≈
			if (delta > 0) {
				MAPMANAGER->setWidthCount(MAPMANAGER->getWidthCount() + 1);
				MAPMANAGER->setHeightCount(MAPMANAGER->getHeightCount() + 1);
			}
			//»Ÿ ≥ª∏∞∞≈
			else if (delta < 0) {
				MAPMANAGER->setWidthCount(MAPMANAGER->getWidthCount() - 1);
				MAPMANAGER->setHeightCount(MAPMANAGER->getHeightCount() - 1);
			}
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
