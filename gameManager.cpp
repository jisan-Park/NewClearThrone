#include "stdafx.h"
#include "gameManager.h"

HRESULT gameManager::init()
{
	master_volume = 100.0f;
	music_volume = 50.0f;
	sfx_volume = 50.0f;

	return S_OK;
}

void gameManager::update()
{
}

void gameManager::release()
{
}

void gameManager::render(HDC hdc)
{
}
