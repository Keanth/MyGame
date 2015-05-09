#include "stdafx.h"
#include "EndGame.h"
#include "MyGame.h"
#include "MainGame.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

EndGame::EndGame()
{
	m_EndGameArr.push_back(String("Yes"));
	m_EndGameArr.push_back(String("No"));

	m_BmpYesPtr = new Bitmap(String("./Assets/Images/ExitBoxYes.png"));
	m_BmpNoPtr = new Bitmap(String("./Assets/Images/ExitBoxNo.png"));
}

EndGame::~EndGame()
{
	delete m_BmpYesPtr;
	m_BmpYesPtr = nullptr;
	delete m_BmpNoPtr;
	m_BmpNoPtr = nullptr;
}

void EndGame::Tick(double deltaTime)
{
}

void EndGame::Paint()
{
	ExitBox();
}

void EndGame::ExitBox()
{
	if (m_Pointer == 0)
	{
		GAME_ENGINE->DrawBitmap(m_BmpYesPtr);
	}
	else
	{
		GAME_ENGINE->DrawBitmap(m_BmpNoPtr);
	}

	if (GAME_ENGINE->IsKeyboardKeyPressed(VK_LEFT))
	{
		m_Pointer--;
		if (m_Pointer == -1)
		{
			m_Pointer = 1;
		}
	}
	else if (GAME_ENGINE->IsKeyboardKeyPressed(VK_RIGHT))
	{
		m_Pointer++;
		if (m_Pointer == 2)
		{
			m_Pointer = 0;
		}
	}
	else if (GAME_ENGINE->IsKeyboardKeyPressed(VK_RETURN) || GAME_ENGINE->IsKeyboardKeyPressed('W'))
	{
		switch (m_Pointer)
		{
		case 0: // YES
			MyGame::InitMainMenu();
			MyGame::m_GameState = GameState::MAIN_MENU;
			break;
		case 1: // NO
			MainGame::m_IsPaused = false;
			break;
		default:
			break;
		}
	}
}