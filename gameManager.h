#pragma once
#include "singletonBase.h"
class gameManager : public singletonBase<gameManager>
{
private:
	////////////////////[ volume ]///////////////////////////
	//back Scene
	tagAlphaImage back;

	//volume front bar
	tagVolume master;
	tagVolume music;
	tagVolume sfx;

	//º¼·ý°ª º¯¼ö
	float master_volume;
	float music_volume;
	float sfx_volume;
	////////////////////[ pause ]///////////////////////////
	bool isPaused;
	bool isSetting;
	//main menum / setting / retry / continue;
	tagAlphaImage pausedBtn[4];

public:
	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);

	////////////////////[ volume ]///////////////////////////

	//getter
	float getMasterVolume() { return master_volume; };
	float getMusicVolume() { return music_volume; };
	float getSfxVolume() { return sfx_volume; };
	//setter
	void setMasterVolume(float f) { master_volume = f; };
	void setMusicVolume(float f) { music_volume = f; };
	void setSfxVolume(float f) { sfx_volume = f; };

	void setVolumeImage();
	void volumeUpdate();
	void volumeRender(HDC hdc);

	////////////////////[ pause ]///////////////////////////
	//getter
	bool getIsPaused() { return isPaused; };
	bool getIsSetting() { return isSetting; };
	//setter
	void setIsPaused(bool b) { isPaused = b; };
	void setIsSetting(bool b) { isSetting = b; };

	void setPauseImage();
	void pauseUpdate();
	void pauseRender(HDC hdc);
};