#pragma once
class SoundManager
{
public:
	SoundManager();
	virtual ~SoundManager();

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	Sound* LoadSound(const String& soundNameRef);

private:
	static const int SIZE = 10;
	Sound* m_SndPtrArr[SIZE];
	String m_SoundNameArr[SIZE];
	int m_NumberOfStoredSounds = 0;
};

