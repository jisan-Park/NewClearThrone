#pragma once
#include "gameNode.h"
class selectScene : public gameNode
{
private:
	//
	tagAlphaImage chr_info[6];

	tagAlphaImage _go;
	tagAlphaImage _back;

	int selectNum;
	image* selectedImage;
public:
	HRESULT init();
	void update();
	void release();
	void render();
	void setImage();
	void selectImage();
	void BtnUpdate();
};