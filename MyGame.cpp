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

#include "SplashScreen.h"
#include "MainMenu.h"
#include "MainGame.h"
#include "Pause.h"
#include "Exit.h"

#include "BitmapManager.h"
#include "SoundManager.h"
#include "IOManager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

GameState MyGame::m_GameState = GameState::SPLASH_SCREEN;

SplashScreen* MyGame::m_SplashScreen = nullptr;
MainMenu* MyGame::m_MainMenu = nullptr;
MainGame* MyGame::m_MainGame = nullptr;
Pause* MyGame::m_Pause = nullptr;
Exit* MyGame::m_Exit = nullptr;

//Managers
BitmapManager* MyGame::m_BitmapManagerPtr = nullptr;
SoundManager* MyGame::m_SoundManagerPtr = nullptr;

//Screen resolution
int MyGame::m_ScreenResWidth = (GetSystemMetrics(SM_CXSCREEN));
int MyGame::m_ScreenResHeight = (GetSystemMetrics(SM_CYSCREEN));

MyGame::MyGame()
{
}

MyGame::~MyGame()
{
}

void MyGame::GameInitialize(GameSettings &gameSettings)
{
	gameSettings.SetWindowTitle(String("MyGame - Lenaerts, Kenneth - 1DAE03"));
	gameSettings.SetWindowWidth(1080);
	gameSettings.SetWindowHeight(720);
	/*gameSettings.SetWindowWidth(m_ScreenResWidth);
	gameSettings.SetWindowHeight(m_ScreenResHeight);*/
	gameSettings.EnableConsole(true);
	gameSettings.EnableAntiAliasing(true);
}

void MyGame::GameStart()
{
	m_IOManagerPtr = new IOManager();
	WriteToLog(0);
	PopulateBank();

	if (m_GameState == GameState::SPLASH_SCREEN)
	{
		InitSplashScreen();
	}
	else if (m_GameState == GameState::MAIN_MENU)
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
	WriteToLog(1);
	delete m_SplashScreen;
	delete m_MainGame;
	delete m_MainMenu;
	delete m_Pause;
	delete m_Exit;
	delete m_BitmapManagerPtr;
	delete m_SoundManagerPtr;
	delete m_IOManagerPtr;
}

void MyGame::GameTick(double deltaTime)
{
	UpdateGameStates(deltaTime);
}

void MyGame::GamePaint(RECT rect)
{
	DrawGameStates();
}

void MyGame::InitSplashScreen()
{
	if (m_SplashScreen == nullptr)
	{
		m_SplashScreen = new SplashScreen();
	}
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
	if (m_GameState == GameState::SPLASH_SCREEN)
	{
		m_SplashScreen->Tick(deltaTime);
	}
	else if (m_GameState == GameState::MAIN_GAME)
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
	if (m_GameState == GameState::SPLASH_SCREEN)
	{
		m_SplashScreen->Paint();
	}
	else if (m_GameState == GameState::MAIN_GAME)
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

void MyGame::PopulateBank()
{
	m_BitmapManagerPtr = new BitmapManager();
	m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/SpriteSheet_Hero.png"));
	m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/Sym.png"));
	m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/SpriteSheet_Npc02.png"));
	m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/SpriteSheet_Npc03.png"));
	m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/Bullet.png"));

	m_SoundManagerPtr = new SoundManager();
	m_SoundManagerPtr->LoadSound(String("./Assets/Sounds/oside_intro.mp3"));
	m_SoundManagerPtr->LoadSound(String("./Assets/Sounds/oside_loop.mp3"));
}

void MyGame::WriteToLog(int number)
{
	switch (number)
	{
	case 0:
		m_IOManagerPtr->AppendToFileBegin("GameResults.txt");
		break;
	case 1:
		m_IOManagerPtr->AppendToFileEnd("GameResults.txt");
		break;
	default:
		break;
	}
}