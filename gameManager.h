#pragma once
#include "singletonBase.h"
enum weaponType;
class gameManager : public singletonBase<gameManager>
{
private:
	////////////////////[ UI ]///////////////////////////
	//���� ����
	tagImage stage;
	tagImage round[2];
	tagImage round_slash;
	//ü�� ����
	tagImage currentHP[2];
	tagImage maxHP[2];

	//ü�¹�
	tagVolume HP;
	tagImage hpSlash;

	//����, ���� �����̹��� + �Ѿ� ����
	tagImage bulletCountNumber[4][3];

	//�Ѿ� �̹����� �����ֱ� //0:bullet, 1:shell, 2:energy, 3:explosive
	tagVolume bulletCount[4];
	////////////////////[ volume ]///////////////////////////
	//back Scene
	tagAlphaImage back;

	//volume front bar
	tagVolume master;
	tagVolume music;
	tagVolume sfx;

	//������ ����
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

	////////////////////[ UI ]///////////////////////////
	void setUIImage();
	void updateUI();
	void UIRender(HDC hdc);
	void getWeaponIcon(image* img, weaponType t);
	////////////////////[ volume ]///////////////////////////
	void volumeCheck();
	
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