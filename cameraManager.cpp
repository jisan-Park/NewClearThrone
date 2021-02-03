#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init()
{
	_camera.setPoint(0,0);
	_sizeX = WINSIZEX;
	_sizeY = WINSIZEY;
	return S_OK;
}

void cameraManager::update()
{
	setClient_Mouse();
}

void cameraManager::release()
{
}

void cameraManager::render()
{
}

void cameraManager::setClient_Mouse()
{
	_client_Mouse.x = _ptMouse.x + _camera.getPoint().x;
	_client_Mouse.y = _ptMouse.y + _camera.getPoint().y;
}

void cameraManager::setSizeX(int i)
{
	_camera.setPointX(i - WINSIZEX / 2);
	//抗寇贸府
	checkCameraPoint();
}

void cameraManager::setSizeY(int i)
{
	_camera.setPointY(i - WINSIZEY / 2);
	//抗寇贸府
	checkCameraPoint();
}

void cameraManager::setCameraPoint(int x, int y)
{
	_camera.setPoint(x - WINSIZEX/2, y - WINSIZEY/2);
	//抗寇贸府
	checkCameraPoint();
}

void cameraManager::checkCameraPoint()
{
	if (_camera.getPoint().x <= 0) {
		_camera.setPointX(0);
	}
	if (_camera.getPoint().x >= TILESIZE * TILEX - WINSIZEX) {
		_camera.setPointX(TILESIZE * TILEX - WINSIZEX);
	}
	if (_camera.getPoint().y <= 0) {
		_camera.setPointY(0);
	}
	if (_camera.getPoint().y >= TILESIZE * TILEY - WINSIZEY) {
		_camera.setPointY(TILESIZE * TILEY - WINSIZEY);
	}
}
