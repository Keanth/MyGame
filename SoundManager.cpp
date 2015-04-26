#include "stdafx.h"
#include "SoundManager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

SoundManager::SoundManager()
{
	for (size_t i = 0; i < SIZE; i++)
	{
		m_SndPtrArr[i] = nullptr;
	}
}

SoundManager::~SoundManager()
{
	for (size_t i = 0; i < SIZE; i++)
	{
		delete m_SndPtrArr[i];
		m_SndPtrArr[i] = nullptr;
	}
}

Sound* SoundManager::LoadSound(const String& soundNameRef)
{
	for (int i = 0; i < m_NumberOfStoredSounds; i++)
	{
		if (m_SoundNameArr[i] == soundNameRef)
		{
			return m_SndPtrArr[i];
		}
	}

	std::wcout << L"The bitmap with path: " << soundNameRef.C_str() << L" is loaded" << std::endl;
	Sound* sndPtr = new Sound(soundNameRef);
	m_SndPtrArr[m_NumberOfStoredSounds] = sndPtr;
	m_SoundNameArr[m_NumberOfStoredSounds] = soundNameRef;
	++m_NumberOfStoredSounds;
	return 0;
}