#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"

effectManager::effectManager()
{
}


effectManager::~effectManager()
{

}

HRESULT effectManager::init()
{
	addEffect("exp", "image/effect/explosion_effect.bmp", 252, 34, 36, 34, 1.0f,0.1f, 1000);
	addEffect("red_exp", "image/effect/rad_explosion_effect.bmp", 252, 36, 34, 34, 1.0f, 0.1f, 1000);
	addEffect("dust", "image/effect/먼지구름.bmp", 133, 19, 19, 19, 1.0f, 0.1f, 1000);
	addEffect("bullet1", "image/effect/총알 터질때 이펙트.bmp", 180, 36, 36, 36, 1.0f, 0.1f, 1000);
	addEffect("bullet2", "image/effect/폭발 이미지.bmp", 800, 200, 100, 100, 1.0f, 0.1f, 1000);

	/*addEffect("longMeele", "image/effect/긴근접 8방향.bmp", 530, 848, 106, 106, 1.0f, 0.1f, 1000);

	addEffect("shotMeele", "image/effect/짧은근접 8방향.bmp", 255, 408, 51, 51, 1.0f, 0.1f, 1000);*/

	addEffect("longSword_0", "image/effect/longSword_0.bmp", 530, 106, 106, 106, 1.0f, 0.1f, 1000);
	addEffect("longSword_1", "image/effect/longSword_1.bmp", 530, 106, 106, 106, 1.0f, 0.1f, 1000);
	addEffect("longSword_2", "image/effect/longSword_2.bmp", 530, 106, 106, 106, 1.0f, 0.1f, 1000);
	addEffect("longSword_3", "image/effect/longSword_3.bmp", 530, 106, 106, 106, 1.0f, 0.1f, 1000);
	addEffect("longSword_4", "image/effect/longSword_4.bmp", 530, 106, 106, 106, 1.0f, 0.1f, 1000);
	addEffect("longSword_5", "image/effect/longSword_5.bmp", 530, 106, 106, 106, 1.0f, 0.1f, 1000);
	addEffect("longSword_6", "image/effect/longSword_6.bmp", 530, 106, 106, 106, 1.0f, 0.1f, 1000);
	addEffect("longSword_7", "image/effect/longSword_7.bmp", 530, 106, 106, 106, 1.0f, 0.1f, 1000);

	addEffect("shortSword_0", "image/effect/shortSword_0.bmp", 255, 51, 51, 51, 1.0f, 0.1f, 1000);
	addEffect("shortSword_1", "image/effect/shortSword_1.bmp", 255, 51, 51, 51, 1.0f, 0.1f, 1000);
	addEffect("shortSword_2", "image/effect/shortSword_2.bmp", 255, 51, 51, 51, 1.0f, 0.1f, 1000);
	addEffect("shortSword_3", "image/effect/shortSword_3.bmp", 255, 51, 51, 51, 1.0f, 0.1f, 1000);
	addEffect("shortSword_4", "image/effect/shortSword_4.bmp", 255, 51, 51, 51, 1.0f, 0.1f, 1000);
	addEffect("shortSword_5", "image/effect/shortSword_5.bmp", 255, 51, 51, 51, 1.0f, 0.1f, 1000);
	addEffect("shortSword_6", "image/effect/shortSword_6.bmp", 255, 51, 51, 51, 1.0f, 0.1f, 1000);
	addEffect("shortSword_7", "image/effect/shortSword_7.bmp", 255, 51, 51, 51, 1.0f, 0.1f, 1000);
	
	
	return S_OK;
}

void effectManager::release()
{
	iterTotalEffect vIter;
	iterEffect mIter;

	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				iterEffects vArrIter = mIter->second.begin();
				for (vArrIter; vArrIter != mIter->second.end(); ++vArrIter)
				{
					(*vArrIter)->release();
					delete *vArrIter;
					vArrIter = mIter->second.erase(vArrIter);
				}
				mIter->second.clear();
			}
			else mIter++;
		}
	}
}

void effectManager::update()
{
	iterTotalEffect vIter;
	iterEffect mIter;

	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->update();
			}
		}
	}
}

void effectManager::render()
{
	iterTotalEffect vIter;
	iterEffect mIter;

	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->render();
			}
		}
	}
}


void effectManager::addEffect(string effectName, const char* imageName, int imageWidth, int imageHeight, int effectWidth, int effectHeight, int fps, float elapsedTime, int buffer)
{
	image* img;
	arrEffects vEffectBuffer;
	arrEffect mArrEffect;

	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else
	{
		img = IMAGEMANAGER->addImage(imageName, imageName, imageWidth, imageHeight, true, RGB(255, 0, 255));
	}

	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, effectWidth, effectHeight, fps, elapsedTime);
	}

	mArrEffect.insert(pair<string, arrEffects>(effectName, vEffectBuffer));

	_vTotalEffects.push_back(mArrEffect);

}


void effectManager::play(string effectName, int x, int y)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == effectName)) break;

			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning()) continue;

				(*vArrIter)->startEffect(x, y);
				return;
			}

		}
	}
}
