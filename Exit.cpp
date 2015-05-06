#include "stdafx.h"
#include "Exit.h"
#include "MyGame.h"
#define GAME_ENGINE (GameEngine::GetSingleton())

Exit::Exit()
{
}

Exit::~Exit()
{
}

void Exit::Tick(double deltaTime)
{
}

void Exit::Paint()
{
	int windowWidth = (GAME_ENGINE->GetWidth() / 2) - 4;
	int windowsHeight = (GAME_ENGINE->GetHeight() / 2) - 1;
	DOUBLE2 strPos(windowWidth, windowsHeight);
	GAME_ENGINE->SetViewMatrix(MATRIX3X2::CreateIdentityMatrix());
	GAME_ENGINE->DrawSolidBackground(COLOR(255, 100, 0));
	GAME_ENGINE->DrawString(String("GAME OVER!"), strPos);
}