#include "stdafx.h"
#include "MyGame.h"
#include "MainGame.h"
#include "LevelOutdoor.h"
#include "Hero.h"
#include "Camera.h"
#include "PolarStarBullet.h"
#include "BulletList.h"
#include "Enemy.h"
#include "EnemyList.h"
#include "HUD.h"
#include "ButtonManager.h"
#include "HealthUp.h"
#include "Doritos.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

DOUBLE2 MainGame::m_HeroPos = DOUBLE2(0.0, 0.0);
bool MainGame::m_IsPaused = false;

MainGame::MainGame()
{
	InitObj();
	InitTestButton();
}

MainGame::~MainGame()
{
	RemoveAll();
}

void MainGame::Tick(double deltaTime)
{
	// ==== <TESTING> =====
	if (GAME_ENGINE->IsKeyboardKeyPressed('L'))
	{
		m_IsPaused = !m_IsPaused;
	}

	for (size_t i = 0; i < m_ButtonManagerPtrArr.size(); ++i)
	{
		m_ButtonManagerPtrArr[i]->CheckIsHit(GAME_ENGINE->GetMousePosition());

	}
	// ==== </TESTING> =====

	CheckTestMenu();

	if (m_IsPaused == false)
	{
		m_LevelOutdoorPtr->Tick(deltaTime);

		m_HeroPtr->Tick(deltaTime);

		PhysicsRendering();

		CameraLock(deltaTime);

		m_EnemyListPtr->Tick(deltaTime);

		m_ArrowListPtr->Tick(deltaTime, m_HeroPtr->GetDirection());

		m_HeroPos = m_HeroPtr->GetPosition();

		m_HealthUpPtr->Tick(deltaTime);
		m_DoritosPtr->Tick(deltaTime);

		_Test();

		if (Hero::m_health <= 0)
		{
			MyGame::InitExit();
			MyGame::m_GameState = GameState::EXIT;
		}
	}

	if (m_IsPaused)
	{
		MyGame::InitPause();
		MyGame::m_GameState = GameState::PAUSE;
	}
}

void MainGame::Paint()
{
	if (m_IsPaused == false)
	{
		m_LevelOutdoorPtr->Paint();

		m_HudPtr->Paint();

		// ==== TESTING =====
		if (m_BoolTestMenu)
		{
			DrawUnderlay();
			for (size_t i = 0; i < m_ButtonManagerPtrArr.size(); i++)
			{
				m_ButtonManagerPtrArr[i]->Paint();
			}
		}
		// ==== TESTING =====
		
		if (m_CameraLock)
		{
			GAME_ENGINE->SetViewMatrix(m_CameraPtr->GetPlayerMatrix());
		}
		else
		{
			GAME_ENGINE->SetViewMatrix(m_CameraPtr->GetViewMatrix());
		}
		m_HeroPtr->Paint();

		m_EnemyListPtr->Paint();

		m_ArrowListPtr->Paint();

		m_HealthUpPtr->Paint();
		m_DoritosPtr->Paint();
	}
	
}

void MainGame::InitObj()
{
	m_HeroPtr = new Hero();
	m_CameraPtr = new Camera(m_HeroPtr);
	m_LevelOutdoorPtr = new LevelOutdoor(m_CameraPtr);
	m_EnemyListPtr = new EnemyList();
	//	EnemyHandler(); //Do not use during testing phase;
	m_ArrowListPtr = new BulletList(m_EnemyListPtr);
	m_HudPtr = new HUD();
	m_HealthUpPtr = new HealthUp(DOUBLE2(400, 5300));
	m_DoritosPtr = new Doritos(DOUBLE2(300, 5270));
}

void MainGame::RemoveAll()
{
	delete m_LevelOutdoorPtr;
	delete m_HeroPtr;
	delete m_CameraPtr;
	delete m_ArrowListPtr;
	delete m_EnemyListPtr;
	delete m_HudPtr;
	delete m_HealthUpPtr;
	delete m_DoritosPtr;

	for (size_t i = 0; i < m_EnemyPtrArr.size(); i++)
	{
		delete m_EnemyPtrArr[i];
		m_EnemyPtrArr[i] = nullptr;
	}
	m_EnemyPtrArr.clear();

	for (size_t i = 0; i < m_ButtonManagerPtrArr.size(); i++)
	{
		delete m_ButtonManagerPtrArr[i];
	}
	m_ButtonManagerPtrArr.clear();
}

void MainGame::PhysicsRendering()
{
	if (GAME_ENGINE->IsKeyboardKeyPressed('P'))
	{
		m_Physics = !m_Physics;
		GAME_ENGINE->EnablePhysicsDebugRendering(m_Physics);
	}
}

void MainGame::CameraLock(double deltaTime)
{
	if (GAME_ENGINE->IsKeyboardKeyPressed('O'))
	{
		m_CameraLock = !m_CameraLock;
	}
	if (!m_CameraLock)
	{
		m_CameraPtr->Tick(deltaTime);
	}
}

void MainGame::EnemyHandler()
{
	for (size_t i = 0; i < 2; i++)
	{
		Enemy* tempPtr = new Enemy(m_LevelOutdoorPtr, m_HeroPtr,
			DOUBLE2(m_HeroPos.x + 30, m_HeroPos.y - 100));
		m_EnemyPtrArr.push_back(tempPtr);
	}
	for (size_t i = 0; i < m_EnemyPtrArr.size(); i++)
	{
		m_EnemyListPtr->Add(m_EnemyPtrArr[i]);
	}
}


// ================ TESTING METHODS ==================
void MainGame::_Test()
{
	if (GAME_ENGINE->IsKeyboardKeyPressed('U'))
	{
		m_EnemyListPtr->Add(new Enemy(m_LevelOutdoorPtr, m_HeroPtr,
			DOUBLE2(m_HeroPos.x + 150, m_HeroPos.y - 100)));
	}
	if (GAME_ENGINE->IsKeyboardKeyPressed('I'))
	{
		m_EnemyListPtr->RemoveAll();
	}
}

void MainGame::InitTestButton()
{
	int posX = 10;
	int posY = 40;
	int offsetX = 120;

	DOUBLE2 position = DOUBLE2(posX + ButtonManager::BUTTON_WIDTH / 2, GAME_ENGINE->GetHeight() - posY + ButtonManager::BUTTON_HEIGHT / 2);
	ButtonManager* localPtr = new ButtonManager(position);
	m_ButtonManagerPtrArr.push_back(localPtr);
	posX += offsetX;

	position = DOUBLE2(posX + ButtonManager::BUTTON_WIDTH / 2, GAME_ENGINE->GetHeight() - posY + ButtonManager::BUTTON_HEIGHT / 2);
	localPtr = new ButtonManager(position);
	m_ButtonManagerPtrArr.push_back(localPtr);
	posX += offsetX;

	position = DOUBLE2(posX + ButtonManager::BUTTON_WIDTH / 2, GAME_ENGINE->GetHeight() - posY + ButtonManager::BUTTON_HEIGHT / 2);
	localPtr = new ButtonManager(position);
	m_ButtonManagerPtrArr.push_back(localPtr);
	posX += offsetX;
}

void MainGame::DrawUnderlay()
{
	int width = GAME_ENGINE->GetWidth();
	int height = GAME_ENGINE->GetHeight();

	RECT r;
	r.bottom = height;
	r.top = r.bottom - 50;
	r.left = 0;
	r.right = r.left + width;

	GAME_ENGINE->SetColor(COLOR(255, 255, 255, 150));

	GAME_ENGINE->SetViewMatrix(MATRIX3X2::CreateIdentityMatrix());
	GAME_ENGINE->FillRect(r);
}

void MainGame::CheckTestMenu()
{
	if (GAME_ENGINE->IsKeyboardKeyPressed('M'))
	{
		m_BoolTestMenu = !m_BoolTestMenu;
	}
}