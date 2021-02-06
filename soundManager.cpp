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
	//FMOD ���� �ʱ�ȭ
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
			//���尡 ��� ����Ϸ��ٺ��ϱ� ��Ű�� �ȳ��Ϳ�!
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
	//�����
	SOUNDMANAGER->addSound("���θ޴�", "sound/���/���θ޴�.mp3", true, true);
	SOUNDMANAGER->addSound("ĳ���ͼ���", "sound/���/ĳ���ͼ���.mp3", true, true);
	SOUNDMANAGER->addSound("��������1", "sound/���/��������1.mp3", true, true);
	SOUNDMANAGER->addSound("��������2", "sound/���/��������2.mp3", true, true);
	SOUNDMANAGER->addSound("��������3", "sound/���/��������3.mp3", true, true);

	//ȿ����
	SOUNDMANAGER->addSound("����������", "sound/�÷��̾� ���/����������.mp3", false, false);
	SOUNDMANAGER->addSound("������������", "sound/�÷��̾� ���/������������.mp3", false, false);
	SOUNDMANAGER->addSound("ũ����Ż������", "sound/�÷��̾� ���/ũ����Ż������.mp3", false, false);
	SOUNDMANAGER->addSound("�÷�Ʈ������", "sound/�÷��̾� ���/�÷�Ʈ������.mp3", false, false);
	SOUNDMANAGER->addSound("�ǽ�������", "sound/�÷��̾� ���/�ǽ�������.mp3", false, false);

	SOUNDMANAGER->addSound("������ ��ų", "sound/������ ��ų.mp3", false, false);
	SOUNDMANAGER->addSound("ũ����Ż ��ų", "sound/ũ����Ż��ų.mp3", false, false);
	SOUNDMANAGER->addSound("�÷�Ʈ ��ų", "sound/�÷�Ʈ ��ų.mp3", false, false);
	SOUNDMANAGER->addSound("�ǽ� ��ų", "sound/�ǽ� ��ų.mp3", false, false);

	SOUNDMANAGER->addSound("Ŭ���Ҹ�", "sound/ȿ����/Ŭ���Ҹ�.mp3", false, false);
	SOUNDMANAGER->addSound("���߻���", "sound/ȿ����/��������.mp3", false, false);

	SOUNDMANAGER->addSound("���ü���", "sound/ȿ����/ĳ���� ����/���� ����.mp3", false, false);
	SOUNDMANAGER->addSound("�÷�Ʈ����", "sound/ȿ����/ĳ���� ����/�÷�Ʈ ����.mp3", false, false);
	SOUNDMANAGER->addSound("�������", "sound/ȿ����/ĳ���� ����/������ ����.mp3", false, false);
	SOUNDMANAGER->addSound("ũ����Ż����", "sound/ȿ����/ĳ���� ����/ũ����Ż����.mp3", false, false);
	SOUNDMANAGER->addSound("�ǽ�����", "sound/ȿ����/ĳ���� ����/�ǽ� ����.mp3", false, false);

	SOUNDMANAGER->addSound("��� �¾�����", "sound/ȿ����/���ʹ�/���/��� �¾�����.mp3", false, false);
	SOUNDMANAGER->addSound("���1", "sound/ȿ����/���ʹ�/���/���1.mp3", false, false);
	SOUNDMANAGER->addSound("���2", "sound/ȿ����/���ʹ�/���/���2.mp3", false, false);

	SOUNDMANAGER->addSound("������ �һձ�", "sound/ȿ����/���ʹ�/������/�һձ�.mp3", false, true);

	SOUNDMANAGER->addSound("��� ������1", "sound/ȿ����/���ʹ�/���/���������1.mp3", false, false);
	SOUNDMANAGER->addSound("��� ������2", "sound/ȿ����/���ʹ�/���/���������2.mp3", false, false);

	SOUNDMANAGER->addSound("�򵶵��°�", "sound/ȿ����/���ʹ�/�򵶵��鼭�ѽ��.mp3", false, true);
	SOUNDMANAGER->addSound("�� ����", "sound/ȿ����/���ʹ�/�򵶵���.mp3", false, false);
	SOUNDMANAGER->addSound("���� ����", "sound/ȿ����/���ʹ�/��������1.mp3", false, false);

	SOUNDMANAGER->addSound("����", "sound/ȿ����/����/����.mp3", false, false);
	SOUNDMANAGER->addSound("�ܹ� ���", "sound/ȿ����/����/�ܹ� ���.mp3", false, false);
	SOUNDMANAGER->addSound("�б�", "sound/ȿ����/����/�б�.mp3", false, false);
	SOUNDMANAGER->addSound("������", "sound/ȿ����/����/������.mp3", false, false);
	SOUNDMANAGER->addSound("��ġ", "sound/ȿ����/����/��ġ.mp3", false, false);
	SOUNDMANAGER->addSound("��Ҹ�", "sound/ȿ����/����/��Ҹ�.mp3", false, false);
	SOUNDMANAGER->addSound("������", "sound/ȿ����/����/������.mp3", false, false);
	SOUNDMANAGER->addSound("������", "sound/ȿ����/����/������.mp3", false, false);
	SOUNDMANAGER->addSound("Į", "sound/ȿ����/����/Į.mp3", false, false);

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
