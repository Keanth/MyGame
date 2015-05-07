#include "stdafx.h"
#include "MyGame.h"
#include "MainMenu.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

MainMenu::MainMenu()
{
	m_MenuArr.push_back(String("Start Game"));
	m_MenuArr.push_back(String("Options"));
	m_MenuArr.push_back(String("Exit"));

	m_FntPixelFontPtr = new Font(String("PixelFont"), 24);
	m_BmpFontPtr = new Bitmap(String("./Assets/Images/MainMenu.png"));
	m_BmpFontSelectedPtr = new Bitmap(String("./Assets/Images/MainMenuSelected.png"));
	m_BmpBackgroundPtr = new Bitmap(String("./Assets/Images/bkMoon.png")); 
}

MainMenu::~MainMenu()
{
	delete m_FntPixelFontPtr;
	m_FntPixelFontPtr = nullptr;
	delete m_BmpFontPtr;
	m_BmpFontPtr = nullptr;
	delete m_BmpFontSelectedPtr;
	m_BmpFontSelectedPtr = nullptr;
	delete m_BmpBackgroundPtr;
	m_BmpBackgroundPtr = nullptr;
}

void MainMenu::Tick(double deltaTime)
{
}

void MainMenu::Paint()
{
//	GAME_ENGINE->DrawSolidBackground(COLOR(255,100,0));
	GAME_ENGINE->DrawBitmap(m_BmpBackgroundPtr);

//	GAME_ENGINE->SetFont(m_FntPixelFontPtr);

	int x = 200;
	int y = 200;
	int dy = 20;

	GAME_ENGINE->SetColor(COLOR(255, 255, 255));

	//Print selected menu item
	for (size_t i = 0; i < m_MenuArr.size(); i++)
	{
		if (i == m_Pointer)
		{
//			GAME_ENGINE->SetColor(COLOR(44, 62, 80));
			GAME_ENGINE->DrawBitmap(m_BmpFontSelectedPtr, DOUBLE2(x, y), Rect(i));
			y += dy;
		}
		else
		{
//			GAME_ENGINE->SetColor(COLOR(255, 255, 255));
			GAME_ENGINE->DrawBitmap(m_BmpFontPtr, DOUBLE2(x, y), Rect(i));
			y += dy;
		}
//		GAME_ENGINE->DrawBitmap(m_BmpFontPtr,DOUBLE2(x,y),Rect(i));
//		GAME_ENGINE->DrawString(String(m_MenuArr[i]), x, y);
//		y += dy;
	}

	if (GAME_ENGINE->IsKeyboardKeyPressed(VK_UP))
	{
		m_Pointer--;
		if (m_Pointer == -1)
		{
			m_Pointer = 2;
		}
	}
	else if (GAME_ENGINE->IsKeyboardKeyPressed(VK_DOWN))
	{
		m_Pointer++;
		if (m_Pointer == 3)
		{
			m_Pointer = 0;
		}
	}
	else if (GAME_ENGINE->IsKeyboardKeyPressed(VK_RETURN))
	{
		switch (m_Pointer)
		{
		case 0: // Game start
			MyGame::InitMainGame();
			MyGame::m_GameState = GameState::MAIN_GAME;
			break;
		case 1: // Game options
			break;
		case 2: // Exit
			GAME_ENGINE->QuitGame();
			break;
		default:
			break;
		}
	}
}

RECT2 MainMenu::Rect(int number)
{
	RECT2 r;
	
	r.top = FONT_HEIGHT * number;
	r.bottom = r.top + FONT_HEIGHT;
	r.left = 0;
	r.right = FONT_WIDTH;

	return r;
}