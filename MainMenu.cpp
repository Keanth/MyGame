#include "stdafx.h"
#include "MyGame.h"
#include "MainMenu.h"
#define GAME_ENGINE (GameEngine::GetSingleton())

MainMenu::MainMenu()
{
	_button = new Button(String("PLAY!"));
	_button->SetBounds(GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight(), 10, 10);
	_button->SetBounds(
		GAME_ENGINE->GetWidth() / 2- _buttonWidth / 2,
		GAME_ENGINE->GetHeight() / 2 - _buttonHeight / 2, 
		_buttonWidth, 
		_buttonHeight);
}

MainMenu::~MainMenu()
{
	RemoveButton();
}

void MainMenu::Tick(double deltaTime)
{
	if (_button->IsPressed())
	{
		RemoveButton();
		m_ButtonIsRemoved = true;
		MyGame::InitMainGame();
		MyGame::m_GameState = GameState::MAIN_GAME;
	}
}

void MainMenu::Paint()
{
	GAME_ENGINE->DrawSolidBackground(COLOR(255,100,0));
}

void MainMenu::RemoveButton()
{
	delete _button;
	_button = nullptr;
}