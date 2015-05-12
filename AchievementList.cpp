#include "stdafx.h"
#include "AchievementList.h"
#include "Achievement.h"
#include "BitmapManager.h"
#include "MyGame.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

AchievementList::AchievementList()
{
	BitmapLoad();
	StringLoad();
//	Add();
}

AchievementList::~AchievementList()
{
	for (size_t i = 0; i < m_AchievementArr.size(); i++)
	{
		delete m_AchievementArr[i];
		m_AchievementArr[i] = nullptr;
	}
	m_AchievementArr.clear();
}

void AchievementList::Add()
{
}

void AchievementList::Tick(double deltaTime)
{
	Conditions();

	for (size_t i = 0; i < m_AchievementArr.size(); i++)
	{
		if (m_CountTick == m_AchievementArr.size()) break;

		if (m_AchievementArr[m_CountTick]->m_IsDone())
		{
			m_CountTick++;
		}
		if ((m_AchievementArr[i]->m_IsDone() == false) && (m_CountTick == i))
		{
			m_AchievementArr[i]->Tick(deltaTime);
		}
	}
}

void AchievementList::Paint()
{
	for (size_t i = 0; i < m_AchievementArr.size(); i++)
	{
		if (m_CountPaint == m_AchievementArr.size()) break;

		if (m_AchievementArr[m_CountPaint]->m_IsDone())
		{
			m_CountPaint++;
		}
		if ((m_AchievementArr[i]->m_IsDone() == false) && (m_CountPaint == i))
		{
			m_AchievementArr[i]->Paint();
		}
	}
}

void AchievementList::BitmapLoad()
{
	m_BmpAchievement1Ptr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/Achievements/AchievementTest.png"));
}

void AchievementList::StringLoad()
{
	m_StrAchievement1 = String("SPASH, SPLASH SCREEN");
	m_StrAchievement2 = String("A new friend, welcome!");
	m_StrAchievement3 = String("MAIN GAME!");
}

void AchievementList::Conditions()
{
	if (MyGame::m_GameState == GameState::SPLASH_SCREEN)
	{
		if (m_BlAchievement1)
		{
			m_BlAchievement1 = false;
			m_AchievementArr.push_back(new Achievement(m_StrAchievement1, m_BmpAchievement1Ptr));
		}
	}
	if (MyGame::m_GameState == GameState::MAIN_MENU)
	{
		if (m_BlAchievement2)
		{
			m_BlAchievement2 = false;
			m_AchievementArr.push_back(new Achievement(m_StrAchievement2, m_BmpAchievement1Ptr));
		}
	}
	if (MyGame::m_GameState == GameState::MAIN_GAME)
	{
		if (m_BlAchievement3)
		{
			m_BlAchievement3 = false;
			m_AchievementArr.push_back(new Achievement(m_StrAchievement3, m_BmpAchievement1Ptr));
		}
	}
}