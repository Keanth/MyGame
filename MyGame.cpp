//-----------------------------------------------------------------
// Game File
// C++ Source - DAEGameV1_2_31.cpp - version v2_16 jan 2015
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------
#include <iostream>
#include <string>
#include "stdafx.h"	
#include "MyGame.h"	

#include "MainMenu.h"
#include "MainGame.h"
#include "Pause.h"
#include "Exit.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

GameState MyGame::m_GameState = GameState::MAIN_GAME;
MainMenu* MyGame::m_MainMenu = nullptr;
MainGame* MyGame::m_MainGame = nullptr;
Pause* MyGame::m_Pause = nullptr;
Exit* MyGame::m_Exit = nullptr;

MyGame::MyGame()
{
}

MyGame::~MyGame()
{
}

void MyGame::GameInitialize(GameSettings &gameSettings)
{
	gameSettings.SetWindowTitle(String("MyGame - Lenaerts, Kenneth - 1DAE03"));
	gameSettings.SetWindowWidth(940);
	gameSettings.SetWindowHeight(640);
	gameSettings.EnableConsole(true);
	gameSettings.EnableAntiAliasing(true);
}

void MyGame::GameStart()
{
	if (m_GameState == GameState::MAIN_MENU)
	{
		InitMainMenu();
	}
	else if (m_GameState == GameState::MAIN_GAME)
	{
		InitMainGame();
	}
}

void MyGame::GameEnd()
{
	delete m_MainGame;
	delete m_MainMenu;
	delete m_Pause;
	delete m_Exit;
}

void MyGame::GameTick(double deltaTime)
{
	UpdateGameStates(deltaTime);
}

void MyGame::GamePaint(RECT rect)
{
	DrawGameStates();
}

void MyGame::InitMainMenu()
{
	if (m_MainMenu == nullptr)
	{
		m_MainMenu = new MainMenu();
	}
}

void MyGame::InitMainGame()
{
	if (m_MainGame == nullptr)
	{
		m_MainGame = new MainGame();
	}
}

void MyGame::InitPause()
{
	if (m_Pause == nullptr)
	{
		m_Pause = new Pause();
	}
}

void MyGame::InitExit()
{
	if (m_Exit == nullptr)
	{
		m_Exit = new Exit();
	}
}

void MyGame::UpdateGameStates(double deltaTime)
{
	if (m_GameState == GameState::MAIN_GAME)
	{
		m_MainGame->Tick(deltaTime);
	}
	else if (m_GameState == GameState::MAIN_MENU)
	{
		m_MainMenu->Tick(deltaTime);
	}
	else if (m_GameState == GameState::PAUSE)
	{
		m_Pause->Tick(deltaTime);
	}
	else if (m_GameState == GameState::EXIT)
	{
		m_Exit->Tick(deltaTime);
	}
}

void MyGame::DrawGameStates()
{
	if (m_GameState == GameState::MAIN_GAME)
	{
		m_MainGame->Paint();
	}
	else if (m_GameState == GameState::MAIN_MENU)
	{
		m_MainMenu->Paint();
	}
	else if (m_GameState == GameState::PAUSE)
	{
		m_Pause->Paint();
	}
	else if (m_GameState == GameState::EXIT)
	{
		m_Exit->Paint();
	}
}

