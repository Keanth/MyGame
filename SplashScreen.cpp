#include "stdafx.h"
#include "SplashScreen.h"
#include "MyGame.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

SplashScreen::SplashScreen()
{
	m_BmpSplashScreenPtr = new Bitmap(String("./Assets/Images/SplashScreen.png"));
}


SplashScreen::~SplashScreen()
{
	delete m_BmpSplashScreenPtr;
	m_BmpSplashScreenPtr = nullptr;
}

void SplashScreen::Tick(double deltaTime)
{
	double time = deltaTime * 100;
	Transition(time);

	/*if ((GAME_ENGINE->IsKeyboardKeyPressed(VK_RETURN)) || (GAME_ENGINE->IsKeyboardKeyPressed('W')))
	{
		MyGame::InitMainMenu();
		MyGame::m_GameState = GameState::MAIN_MENU;
	}*/
}

void SplashScreen::Paint()
{
	int width = GAME_ENGINE->GetWidth();
	int height = GAME_ENGINE->GetHeight();
	GAME_ENGINE->DrawSolidBackground(COLOR(0, 0, 0));
	GAME_ENGINE->DrawBitmap(m_BmpSplashScreenPtr);
	GAME_ENGINE->SetColor(COLOR(0, 0, 0, int(m_Opacity)));
	GAME_ENGINE->FillRect(DOUBLE2(0, 0), DOUBLE2(width, height));
}

void SplashScreen::Transition(double time)
{
	if (m_CountDown == false)
	{
		m_Opacity -= time;
	}
	if (m_Opacity <= 10)
	{
		m_CountDown = true;
	}
	if (m_CountDown)
	{
		m_Opacity += time;
		m_CountUp = true;
	}
	if ((m_CountUp) && m_Opacity >= 240)
	{
		MyGame::InitMainMenu();
		MyGame::m_GameState = GameState::MAIN_MENU;
	}
}