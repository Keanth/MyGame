#include "stdafx.h"
#include "BitmapManager.h"
#define GAME_ENGINE (GameEngine::GetSingleton())

BitmapManager::BitmapManager()
{
	for (size_t i = 0; i < SIZE; i++)
	{
		m_BmpPtrArr[i] = nullptr;
	}
}


BitmapManager::~BitmapManager()
{
	for (int i = 0; i < m_NumberOfStoredBitmaps; i++)
	{
		delete m_BmpPtrArr[i];
		m_BmpPtrArr[i] = nullptr;
	}
}

Bitmap* BitmapManager::LoadBitmap(const String& fileNameRef)
{
	for (int i = 0; i < m_NumberOfStoredBitmaps; i++)
	{
		if (m_FileNameArr[i] == fileNameRef)
		{
			return m_BmpPtrArr[i];
		}
	}
	
	std::wcout << L"The bitmap with path: " << fileNameRef.C_str() << L" is loaded" << std::endl;
	Bitmap* bmpPtr = new Bitmap(fileNameRef);
	m_BmpPtrArr[m_NumberOfStoredBitmaps] = bmpPtr;
	m_FileNameArr[m_NumberOfStoredBitmaps] = fileNameRef;
	++m_NumberOfStoredBitmaps;
	return 0;
//	return bmpPtr;
}