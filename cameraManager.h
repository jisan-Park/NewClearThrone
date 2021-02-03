#pragma once
#include "singletonBase.h"
#include "camera.h"
class cameraManager : public singletonBase<cameraManager>
{
private:
	camera _camera;
	POINT _client_Mouse;

	int _sizeX;
	int _sizeY;
public:
	HRESULT init();
	void update();
	void release();
	void render();
	//setter
	void setClient_Mouse();
	void setSizeX(int i);
	void setSizeY(int i);
	void setCameraPoint(int x, int y);
	void setCameraPointX(int x) { _camera.setPointX(x); };
	void setCameraPointY(int y) { _camera.setPointY(y); };
	//getter
	POINT getMousePoint() { return _client_Mouse; };
	int getSizeX() { return _sizeX; };
	int getSizeY() { return _sizeY; };
	POINT getCameraPoint() { return _camera.getPoint(); };
	//update
	void checkCameraPoint();
};

