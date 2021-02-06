#include "stdafx.h"
#include "soundManager.h"

soundManager::soundManager()
	: _system(nullptr),
	_channel(nullptr),
	_sound(nullptr)
{
}

soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
	//FMOD 엔진 초기화
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);
	setSound();
	return S_OK;
}

void soundManager::release()
{
	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}

	delete[] _sound;
	delete[] _channel;
}

void soundManager::update()
{
	_system->update();
}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);

		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);

		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void soundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드가 계속 재생하려다보니까 끊키고 안나와요!
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}



void soundManager::setVolume(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setVolume(volume);
			break;
		}
	}

}

void soundManager::setSound()
{
	//배경음
	SOUNDMANAGER->addSound("메인메뉴", "sound/배경/메인메뉴.mp3", true, true);
	SOUNDMANAGER->addSound("캐릭터선택", "sound/배경/캐릭터선택.mp3", true, true);
	SOUNDMANAGER->addSound("스테이지1", "sound/배경/스테이지1.mp3", true, true);
	SOUNDMANAGER->addSound("스테이지2", "sound/배경/스테이지2.mp3", true, true);
	SOUNDMANAGER->addSound("스테이지3", "sound/배경/스테이지3.mp3", true, true);

	//효과음
	SOUNDMANAGER->addSound("멜팅죽을떄", "sound/플레이어 사망/멜팅죽을때.mp3", false, false);
	SOUNDMANAGER->addSound("아이즈죽을때", "sound/플레이어 사망/아이즈죽을때.mp3", false, false);
	SOUNDMANAGER->addSound("크리스탈죽을때", "sound/플레이어 사망/크리스탈죽을때.mp3", false, false);
	SOUNDMANAGER->addSound("플랜트죽을때", "sound/플레이어 사망/플랜트죽을대.mp3", false, false);
	SOUNDMANAGER->addSound("피쉬죽을때", "sound/플레이어 사망/피쉬죽을때.mp3", false, false);

	SOUNDMANAGER->addSound("아이즈 스킬", "sound/아이즈 스킬.mp3", false, false);
	SOUNDMANAGER->addSound("크리스탈 스킬", "sound/크리스탈스킬.mp3", false, false);
	SOUNDMANAGER->addSound("플랜트 스킬", "sound/플랜트 스킬.mp3", false, false);
	SOUNDMANAGER->addSound("피쉬 스킬", "sound/피쉬 스킬.mp3", false, false);

	SOUNDMANAGER->addSound("클릭소리", "sound/효과음/클릭소리.mp3", false, false);
	SOUNDMANAGER->addSound("폭발사운드", "sound/효과음/폭빌사운드.mp3", false, false);

	SOUNDMANAGER->addSound("멜팅선택", "sound/효과음/캐릭터 선택/멜팅 선택.mp3", false, false);
	SOUNDMANAGER->addSound("플랜트선택", "sound/효과음/캐릭터 선택/플랜트 선택.mp3", false, false);
	SOUNDMANAGER->addSound("아이즈선택", "sound/효과음/캐릭터 선택/아이즈 선택.mp3", false, false);
	SOUNDMANAGER->addSound("크리스탈선택", "sound/효과음/캐릭터 선택/크리스탈선택.mp3", false, false);
	SOUNDMANAGER->addSound("피쉬선택", "sound/효과음/캐릭터 선택/피쉬 선택.mp3", false, false);

	SOUNDMANAGER->addSound("까마귀 맞았을때", "sound/효과음/에너미/까마귀/까마귀 맞았을때.mp3", false, false);
	SOUNDMANAGER->addSound("까마귀1", "sound/효과음/에너미/까마귀/까마귀1.mp3", false, false);
	SOUNDMANAGER->addSound("까마귀2", "sound/효과음/에너미/까마귀/까마귀2.mp3", false, false);

	SOUNDMANAGER->addSound("도마뱀 불뿜기", "sound/효과음/에너미/도마뱀/불뿜기.mp3", false, true);

	SOUNDMANAGER->addSound("잡몹 죽을때1", "sound/효과음/에너미/잡몹/잡몹죽을때1.mp3", false, false);
	SOUNDMANAGER->addSound("잡몹 죽을때2", "sound/효과음/에너미/잡몹/잡몹죽을때2.mp3", false, false);

	SOUNDMANAGER->addSound("빅독도는거", "sound/효과음/에너미/빅독돌면서총쏘는.mp3", false, true);
	SOUNDMANAGER->addSound("빅독 등장", "sound/효과음/에너미/빅독등장.mp3", false, false);
	SOUNDMANAGER->addSound("빅밴딧 등장", "sound/효과음/에너미/빅밴딧등장1.mp3", false, false);

	SOUNDMANAGER->addSound("권총", "sound/효과음/무기/권총.mp3", false, false);
	SOUNDMANAGER->addSound("단발 쎈거", "sound/효과음/무기/단발 쎈거.mp3", false, false);
	SOUNDMANAGER->addSound("둔기", "sound/효과음/무기/둔기.mp3", false, false);
	SOUNDMANAGER->addSound("레이저", "sound/효과음/무기/레이저.mp3", false, false);
	SOUNDMANAGER->addSound("렌치", "sound/효과음/무기/렌치.mp3", false, false);
	SOUNDMANAGER->addSound("쇠소리", "sound/효과음/무기/쇠소리.mp3", false, false);
	SOUNDMANAGER->addSound("약한총", "sound/효과음/무기/약한총.mp3", false, false);
	SOUNDMANAGER->addSound("재장전", "sound/효과음/무기/재장전.mp3", false, false);
	SOUNDMANAGER->addSound("칼", "sound/효과음/무기/칼.mp3", false, false);

}

unsigned int soundManager::getPosition(string keyName)
{
	unsigned int position;

	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPosition(&position, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return position;
}

unsigned int soundManager::getLength(string keyName)
{
	unsigned int total;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->getLength(&total, FMOD_TIMEUNIT_MS);
			//_sound[count]->getLength(&total, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return total;
}

void soundManager::setPosition(string keyName, int position)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPosition(position, FMOD_TIMEUNIT_MS);
			break;
		}
	}
}
