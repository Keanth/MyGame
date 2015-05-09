#include "stdafx.h"
#include "DialogueTree.h"
#include "MyGame.h"
#include "MainGame.h"
#include "BitmapManager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

DialogueTree::DialogueTree()
{
	m_FontPtr = new Font(String(""), 32);

	//Populate
	m_DialogueTreeArr.push_back(String("CURLYHAPPY"));
	m_DialogueTreeArr.push_back(String("HEY!!"));
	m_DialogueTreeArr.push_back(String("Get moving!"));
	m_DialogueTreeArr.push_back(String("Are you sleeping?"));
	m_DialogueTreeArr.push_back(String("WAKE UP!!"));
	m_DialogueTreeArr.push_back(String("It's time to go,"));
	m_DialogueTreeArr.push_back(String("race you to the top!"));
	m_DialogueTreeArr.push_back(String("QUOTE"));
	m_DialogueTreeArr.push_back(String("..."));
	m_DialogueTreeArr.push_back(String("END1"));

	//init boxes
	m_BmpCurlyHappyPtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/Dialogue/CurlyHappy.png"));
	m_BmpQuotePtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/Dialogue/Quote.png"));

	//Cursor thingy
	m_BmpCursorPtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/HUD.png"));
}

DialogueTree::~DialogueTree()
{
	delete m_FontPtr;
	m_FontPtr = nullptr;
	m_DialogueTreeArr.clear();
}

void DialogueTree::Tick(double deltaTime)
{
	Cursor(1, deltaTime);

	if ((GAME_ENGINE->IsKeyboardKeyPressed(VK_RETURN)) || (GAME_ENGINE->IsKeyboardKeyPressed('W')))
	{
		m_Pointer++;
	}
}

void DialogueTree::Paint()
{
	DialogueLoop();
	Cursor(0, 0);
}

void DialogueTree::DialogueLoop()
{
	DOUBLE2 boxPos(100, 500);
	DOUBLE2 strPos;
	strPos.x = boxPos.x + 150;
	strPos.y = boxPos.y + 25;

	GAME_ENGINE->SetFont(m_FontPtr);
	GAME_ENGINE->SetColor(COLOR(255, 255, 255));

	for (size_t i = 0; i < m_DialogueTreeArr.size(); i++)
	{
		if (m_Pointer == i)
		{
			if (m_DialogueTreeArr[i] == String("CURLYHAPPY"))
			{
				m_DialogueState = DialogueState::CURLYHAPPY;
				m_Pointer++;
			}
			else if (m_DialogueTreeArr[i] == String("QUOTE"))
			{
				m_DialogueState = DialogueState::QUOTE;
				m_Pointer++;
			}
			else if (m_DialogueTreeArr[i] == String("END1"))
			{
				MainGame::m_DialogueActive = false;
				MainGame::m_IsPaused = false;
			}
			switch (m_DialogueState)
			{
			case DialogueTree::DialogueState::CURLYHAPPY:
				GAME_ENGINE->DrawBitmap(m_BmpCurlyHappyPtr, boxPos);
				GAME_ENGINE->DrawString(m_DialogueTreeArr[i], strPos);
				break;
			case DialogueTree::DialogueState::QUOTE:
				GAME_ENGINE->DrawBitmap(m_BmpQuotePtr, boxPos);
				GAME_ENGINE->DrawString(m_DialogueTreeArr[i], strPos);
				break;
			default:
				break;
			}
		}
	}
}

void DialogueTree::Cursor(int number, double deltaTime)
{
	double time = 0.3;
	int cursosPosY = 0;
	int initPos = 560;
	int dy = 5;

	switch (number)
	{
	case 0:
		if (m_IsCursor == false)
		{
			cursosPosY = initPos;
		}
		if (m_IsCursor)
		{
			cursosPosY = initPos + dy;
		}
		GAME_ENGINE->DrawBitmap(m_BmpCursorPtr, DOUBLE2(570, cursosPosY), CursorRect());
		break;
	case 1:
		m_CursorCount += deltaTime;

		if ((m_CursorCount >= time) && (m_IsCursor))
		{
			m_CursorCount = 0;
			m_IsCursor = false;
		}
		else if (m_CursorCount >= time)
		{
			m_CursorCount = 0;
			m_IsCursor = true;
		}
		break;
	default:
		break;
	}
}

RECT2 DialogueTree::CursorRect()
{
	RECT2 r;

	r.top = MyGame::TILE_SIZE * 8;
	r.bottom = r.top + MyGame::TILE_SIZE;
	r.left = 0;
	r.right = 14;

	return r;
}