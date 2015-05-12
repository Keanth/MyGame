#include "stdafx.h"
#include "Achievement.h"
#include "BitmapManager.h"
#include "MyGame.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Achievement::Achievement(String text, Bitmap* bmp)
:m_AchievementText(text), m_BmpAchievementPicturePtr(bmp)
{
	m_BmpAchievementBoxPtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/AchievementBox.png"));
	m_PosY = GAME_ENGINE->GetHeight();
}

Achievement::~Achievement()
{
}

void Achievement::Tick(double deltaTime)
{
	AchievementBox(deltaTime);
}

void Achievement::Paint()
{
	GAME_ENGINE->SetDefaultFont();
	GAME_ENGINE->DrawBitmap(m_BmpAchievementBoxPtr, m_Pos);
	AchievementText(m_AchievementText);
	AchievementPicture(m_BmpAchievementPicturePtr);
}

void Achievement::AchievementBox(double deltaTime) // Get the positions for the box
{
	int screenWidth = GAME_ENGINE->GetWidth();
	int screenHeight = GAME_ENGINE->GetHeight();
	int bmpWidth = m_BmpAchievementBoxPtr->GetWidth();
	int bmpHeigh = m_BmpAchievementBoxPtr->GetHeight();
	int offset = 2;
	int timeDelay = 3;
	m_PosCapY = screenHeight - bmpHeigh;

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
	}

	m_Pos = DOUBLE2(screenWidth - bmpWidth, m_PosY);
}

void Achievement::AchievementText(String &str)
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

void Achievement::AchievementPicture(Bitmap* &bmp) // Pic size : 50 x 50 
{
	double posX = m_Pos.x + 22;
	double posY = m_Pos.y + 23;
	DOUBLE2 pos(posX, posY);

	GAME_ENGINE->DrawBitmap(bmp, pos);
}

bool Achievement::m_IsDone()
{
	int screenHeight = GAME_ENGINE->GetHeight();

	if (m_PosY < screenHeight)
	{
		m_Check = true;
	}
	if ((m_Check) && (m_PosY >= screenHeight))
	{
		return true;
	}
	return false;
}