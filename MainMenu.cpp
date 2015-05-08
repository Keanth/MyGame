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

	m_BmpBackgroundPtr = new Bitmap(String("./Assets/Images/Level_Outdoor_Bg.png")); 
	m_BmpLevelOutdoor1Ptr = new Bitmap(String("./Assets/Images/Level_Outdoor_1.png"));
	m_BmpLevelOutdoor2Ptr = new Bitmap(String("./Assets/Images/Level_Outdoor_2.png"));
	m_BmpLevelOutdoor3Ptr = new Bitmap(String("./Assets/Images/Level_Outdoor_3.png"));
	m_BmpLevelOutdoor4Ptr = new Bitmap(String("./Assets/Images/Level_Outdoor_4.png"));

	m_BitmapWidth = m_BmpLevelOutdoor1Ptr->GetWidth();
	Background(2,0);
}

MainMenu::~MainMenu()
{
	delete m_FntPixelFontPtr;
	m_FntPixelFontPtr = nullptr;
	delete m_BmpFontPtr;
	m_BmpFontPtr = nullptr;
	delete m_BmpFontSelectedPtr;
	m_BmpFontSelectedPtr = nullptr;
	Background(3, 0);
}

void MainMenu::Tick(double deltaTime)
{
	Background(1, deltaTime);

	m_Count += deltaTime;

	if (m_Count > 0.6)
	{
		m_Count = 0;
	}
	if ((GAME_ENGINE->IsKeyboardKeyPressed('W')) || (GAME_ENGINE->IsKeyboardKeyPressed(VK_RETURN)))
	{
		m_Menu = true;
	}
}

void MainMenu::Paint()
{	
	Background(0,0);
	Menu();	
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

void MainMenu::Menu()
{
	int x = 200;
	int y = 200;
	int dy = 30;

	GAME_ENGINE->SetColor(COLOR(255, 255, 255));

	//Print selected menu item
	for (size_t i = 0; i < m_MenuArr.size(); i++)
	{
		if (i == m_Pointer)
		{
			if (m_Count < 0.3)
			{
				GAME_ENGINE->DrawBitmap(m_BmpFontSelectedPtr, DOUBLE2(x, y), Rect(i));
			}
			else
			{
				GAME_ENGINE->DrawBitmap(m_BmpFontPtr, DOUBLE2(x, y), Rect(i));
			}
			y += dy;
		}
		else
		{
			GAME_ENGINE->DrawBitmap(m_BmpFontPtr, DOUBLE2(x, y), Rect(i));
			y += dy;
		}
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
	else if (GAME_ENGINE->IsKeyboardKeyPressed(VK_RETURN) || GAME_ENGINE->IsKeyboardKeyPressed('W'))
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

void MainMenu::Background(int number, double deltaTime)
{
	int offset = 1;

	switch (number)
	{
	case 0:
		GAME_ENGINE->DrawBitmap(m_BmpBackgroundPtr);
		BackgroundPaint();
		break;
	case 1:
		BackgroundLoop();

		m_Pos1.x += deltaTime * 32;
		m_Pos2.x += deltaTime * 16;
		m_Pos3.x += deltaTime * 8;
		m_Pos4.x += deltaTime * 4;

		m_Pos12.x += (deltaTime * 32);
		m_Pos22.x += (deltaTime * 16);
		m_Pos32.x += (deltaTime * 8);
		m_Pos42.x += (deltaTime * 4);
		break;
	case 2:
		m_Pos12.x = -m_BitmapWidth + offset;
		m_Pos22.x = -m_BitmapWidth + offset;
		m_Pos32.x = -m_BitmapWidth + offset;
		m_Pos42.x = -m_BitmapWidth + offset;
		break;
	case 3:
		delete m_BmpBackgroundPtr;
		m_BmpBackgroundPtr = nullptr;
		delete m_BmpLevelOutdoor1Ptr;
		m_BmpLevelOutdoor1Ptr = nullptr;
		delete m_BmpLevelOutdoor2Ptr;
		m_BmpLevelOutdoor2Ptr = nullptr;
		delete m_BmpLevelOutdoor3Ptr;
		m_BmpLevelOutdoor3Ptr = nullptr;
		delete m_BmpLevelOutdoor4Ptr;
		m_BmpLevelOutdoor4Ptr = nullptr;
		break;
	default:
		break;
	}
}

void MainMenu::BackgroundPaint()
{
	GAME_ENGINE->DrawBitmap(m_BmpLevelOutdoor4Ptr, m_Pos1);
	GAME_ENGINE->DrawBitmap(m_BmpLevelOutdoor4Ptr, m_Pos12);

	GAME_ENGINE->DrawBitmap(m_BmpLevelOutdoor3Ptr, m_Pos2);
	GAME_ENGINE->DrawBitmap(m_BmpLevelOutdoor3Ptr, m_Pos22);

	GAME_ENGINE->DrawBitmap(m_BmpLevelOutdoor2Ptr, m_Pos3);
	GAME_ENGINE->DrawBitmap(m_BmpLevelOutdoor2Ptr, m_Pos32);

	GAME_ENGINE->DrawBitmap(m_BmpLevelOutdoor1Ptr, m_Pos4);
	GAME_ENGINE->DrawBitmap(m_BmpLevelOutdoor1Ptr, m_Pos42);
}

void MainMenu::BackgroundLoop()
{
	int offset = 3;

	if (m_Pos1.x > m_BitmapWidth)
	{
		m_Pos1.x = -m_BitmapWidth + offset;
	}
	if (m_Pos12.x > m_BitmapWidth)
	{
		m_Pos12.x = -m_BitmapWidth;
	}

	if (m_Pos2.x > m_BitmapWidth)
	{
		m_Pos2.x = -m_BitmapWidth + offset;
	}
	if (m_Pos22.x > m_BitmapWidth)
	{
		m_Pos22.x = -m_BitmapWidth;
	}

	if (m_Pos3.x > m_BitmapWidth)
	{
		m_Pos3.x = -m_BitmapWidth + offset;
	}
	if (m_Pos32.x > m_BitmapWidth)
	{
		m_Pos32.x = -m_BitmapWidth;
	}

	if (m_Pos4.x > m_BitmapWidth)
	{
		m_Pos4.x = -m_BitmapWidth + offset;
	}
	if (m_Pos42.x > m_BitmapWidth)
	{
		m_Pos42.x = -m_BitmapWidth;
	}	
}