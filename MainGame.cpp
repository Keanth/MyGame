#include "stdafx.h"
#include "MyGame.h"
#include "MainGame.h"
#include "LevelOutdoor.h"
#include "Hero.h"
#include "Camera.h"
#include "PolarStarBullet.h"
#include "BulletList.h"
#include "GraveKeeper.h"
#include "EnemyList.h"
#include "HUD.h"
#include "ButtonManager.h"
#include "HealthUp.h"
#include "Doritos.h"
#include "PickUpList.h"
#include "SoundManager.h"
#include "NightSpirit.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

DOUBLE2 MainGame::m_HeroPos = DOUBLE2(0.0, 0.0);
bool MainGame::m_IsPaused = false;
PickUpList* MainGame::m_PickUpListPtr = nullptr;

MainGame::MainGame()
{
	InitObj();
	InitTestButton();
}

void MainGame::InitObj()
{
	m_HeroPtr = new Hero();
	m_CameraPtr = new Camera(m_HeroPtr);
	m_LevelOutdoorPtr = new LevelOutdoor(m_CameraPtr);
	m_PickUpListPtr = new PickUpList(m_HeroPtr);
	m_EnemyListPtr = new EnemyList(m_HeroPtr);
	m_BulletListPtr = new BulletList(m_EnemyListPtr);
	m_HudPtr = new HUD();

	m_HeroPtr->SetBulletList(m_BulletListPtr);
}

MainGame::~MainGame()
{
	RemoveAll();
}

void MainGame::RemoveAll()
{
	delete m_LevelOutdoorPtr;
	delete m_HeroPtr;
	delete m_CameraPtr;
	delete m_BulletListPtr;
	delete m_EnemyListPtr;
	delete m_HudPtr;
	delete m_PickUpListPtr;

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

		if (GAME_ENGINE->IsKeyboardKeyPressed('V'))
		{
			std::cout << int(m_HeroPos.x) << "  " << int(m_HeroPos.y) << std::endl;
		}

		PhysicsRendering();

		CameraLock(deltaTime);

		m_EnemyListPtr->Tick(deltaTime);

		m_BulletListPtr->Tick(deltaTime, m_HeroPtr->GetDirection());

		m_HeroPos = m_HeroPtr->GetPosition();

		PopulatePickUpList();
		m_PickUpListPtr->Tick(deltaTime);

		if (m_EnemySpawn)
		{
			EnemyHandler();
			m_EnemySpawn = false;
		}

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

	m_BulletListPtr->Paint();

	m_PickUpListPtr->Paint();
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
	m_EnemyListPtr->Add(new GraveKeeper(m_LevelOutdoorPtr, m_HeroPtr,
		DOUBLE2(275,5040)));
	m_EnemyListPtr->Add(new GraveKeeper(m_LevelOutdoorPtr, m_HeroPtr,
		DOUBLE2(300, 3888)));
	m_EnemyListPtr->Add(new GraveKeeper(m_LevelOutdoorPtr, m_HeroPtr,
		DOUBLE2(400, 3888)));
	m_EnemyListPtr->Add(new GraveKeeper(m_LevelOutdoorPtr, m_HeroPtr,
		DOUBLE2(587, 3440)));
}

void MainGame::PopulateSound()
{
	
}

void MainGame::PopulatePickUpList()
{
	if (GAME_ENGINE->IsKeyboardKeyPressed('X'))
	{
		m_PickUpListPtr->Add(new Doritos(DOUBLE2(300, 5270), m_HeroPtr));
		m_PickUpListPtr->Add(new HealthUp(DOUBLE2(400, 5300), m_HeroPtr));
	}
}

// ================ TESTING METHODS ==================
void MainGame::_Test()
{
	if (GAME_ENGINE->IsKeyboardKeyPressed('U'))
	{
		m_EnemyListPtr->Add(new GraveKeeper(m_LevelOutdoorPtr, m_HeroPtr,
			DOUBLE2(m_HeroPos.x + 150, m_HeroPos.y - 100)));
	}
	if (GAME_ENGINE->IsKeyboardKeyPressed('N'))
	{
		m_EnemyListPtr->Add(new NightSpirit(m_LevelOutdoorPtr, m_HeroPtr,
			DOUBLE2(m_HeroPos.x + 150, m_HeroPos.y - 100), m_BulletListPtr));
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