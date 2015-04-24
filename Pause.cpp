#include "stdafx.h"
#include "Pause.h"
#include "MainGame.h"
#include "MyGame.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Pause::Pause()
{
}


Pause::~Pause()
{
}

void Pause::Tick(double deltaTime)
{
	if (GAME_ENGINE->IsKeyboardKeyPressed('L'))
	{
		MainGame::m_IsPaused = !MainGame::m_IsPaused;
		MyGame::InitMainGame();
		MyGame::m_GameState = GameState::MAIN_GAME;
	}
}

void Pause::Paint()
{
	int windowWidth = (GAME_ENGINE->GetWidth() / 2) - 4;
	int windowsHeight = (GAME_ENGINE->GetHeight() / 2) - 1;
	DOUBLE2 strPos(windowWidth, windowsHeight);
	GAME_ENGINE->SetViewMatrix(MATRIX3X2::CreateIdentityMatrix());
//	GAME_ENGINE->DrawSolidBackground(COLOR(255, 100, 0));
	GAME_ENGINE->DrawString(String("PAUSED!"), strPos);
}