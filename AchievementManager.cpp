#include "stdafx.h"
#include "AchievementManager.h"
#include "BitmapManager.h"
#include "MyGame.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

AchievementManager::AchievementManager()
{
	m_BmpAchievementBoxPtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/AchievementBox.png"));
	m_BmpAchievementPicturePtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/Achievements/AchievementTest.png"));
	m_PosY = GAME_ENGINE->GetHeight();
}

AchievementManager::~AchievementManager()
{
}

void AchievementManager::Tick(double deltaTime)
{
	if (Conditions(1))
	{
		AchievementBox(deltaTime);
	}
}

void AchievementManager::Paint()
{
	Conditions(0);
}

bool AchievementManager::Conditions(int number)
{
	if (MyGame::m_GameState == GameState::SPLASH_SCREEN)
	{
		switch (number)
		{
		case 0:
			GAME_ENGINE->DrawBitmap(m_BmpAchievementBoxPtr, m_Pos);
			AchievementText(String("SPLASH SCREEN MOFO!"));
			AchievementPicture(m_BmpAchievementPicturePtr);
			break;
		case 1:
			m_AchievementChecked = false;
			return true;
			break;
		}
	}
	if (MyGame::m_GameState == GameState::MAIN_MENU)
	{
		switch (number)
		{
		case 0:
			GAME_ENGINE->DrawBitmap(m_BmpAchievementBoxPtr, m_Pos);
			AchievementText(String("A new friend, welcome!"));
			AchievementPicture(m_BmpAchievementPicturePtr);
			break;
		case 1:
			m_AchievementChecked = false;
			return true;
			break;
		}
	}
	return false;
}

void AchievementManager::AchievementBox(double deltaTime) // Get the positions for the box
{
	int screenWidth = GAME_ENGINE->GetWidth();
	int screenHeight = GAME_ENGINE->GetHeight();
	int bmpWidth = m_BmpAchievementBoxPtr->GetWidth();
	int bmpHeigh = m_BmpAchievementBoxPtr->GetHeight();
	int offset = 2;
	int timeDelay = 3;
	m_PosCapY = screenHeight - bmpHeigh;

	if (m_AchievementChecked == false)
	{
		if (m_TimeDone == false)
		{
			m_PosY -= offset;
		}
		if ((m_PosY <= m_PosCapY) && (m_TimeDone == false))
		{
			m_PosY = m_PosCapY;
			m_Time += deltaTime;
		}
		if (m_Time >= timeDelay)
		{
			m_TimeDone = true;
			m_Time = 0;
		}
		if (m_TimeDone)
		{
			m_PosY += offset;
		}
		if ((m_PosY >= screenHeight) && (m_TimeDone))
		{
			m_Time = 0;
			m_TimeDone = false;
			m_AchievementChecked = true;
		}
	}

	m_Pos = DOUBLE2(screenWidth - bmpWidth, m_PosY);
}

void AchievementManager::AchievementText(String &str)
{
	double posX = m_Pos.x + 100;
	double posY = m_Pos.y + 25;
	DOUBLE2 pos(posX, posY);

	GAME_ENGINE->SetColor(COLOR(255, 255, 255));
	GAME_ENGINE->DrawString(String("Achievement unlocked!"), pos);

	posY += 30;
	pos = DOUBLE2(posX, posY);
	GAME_ENGINE->DrawString(str, pos);
}

void AchievementManager::AchievementPicture(Bitmap* &bmp) // Pic size : 50 x 50 
{
	double posX = m_Pos.x + 22;
	double posY = m_Pos.y + 23;
	DOUBLE2 pos(posX, posY);

	GAME_ENGINE->DrawBitmap(bmp, pos);
}