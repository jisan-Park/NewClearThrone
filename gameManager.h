#pragma once
#include "singletonBase.h"
class gameManager : public singletonBase<gameManager>
{
private:
	//º¼·ý°ª º¯¼ö
	float master_volume;
	float music_volume;
	float sfx_volume;

public:
	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);

	//getter
	float getMasterVolume() { return master_volume; };
	float getMusicVolume() { return music_volume; };
	float getSfxVolume() { return sfx_volume; };
	//setter
	void setMasterVolume(float f) { master_volume = f; };
	void setMusicVolume(float f) { music_volume = f; };
	void setSfxVolume(float f) { sfx_volume = f; };
};