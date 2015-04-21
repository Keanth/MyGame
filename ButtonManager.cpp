#include "stdafx.h"
#include "ButtonManager.h"
#define GAME_ENGINE	(GameEngine::GetSingleton())

ButtonManager::ButtonManager(DOUBLE2 position)
:m_Position(position)
{
	m_ActIsOnPtr = new PhysicsActor(position, 0, BodyType::STATIC);
	m_ActIsOnPtr->SetGhost(true);
	m_ActIsOnPtr->AddBoxShape(BUTTON_WIDTH, BUTTON_HEIGHT);
}

ButtonManager::~ButtonManager()
{
	delete m_ActIsOnPtr;
}

void ButtonManager::Tick(double deltaTime)
{

}

void ButtonManager::Paint()
{
	GAME_ENGINE->SetColor(COLOR(200, 0, 20));
	DOUBLE2 position = DOUBLE2(m_Position.x - BUTTON_WIDTH / 2, m_Position.y - BUTTON_HEIGHT / 2);
	GAME_ENGINE->FillRect(position, DOUBLE2(position.x + BUTTON_WIDTH, position.y + BUTTON_HEIGHT));

	GAME_ENGINE->SetColor(COLOR(0, 0, 0));
	GAME_ENGINE->DrawString(String(m_HitCntr), m_Position);
}

bool ButtonManager::CheckIsHit(POINT p)
{
	if (GAME_ENGINE->IsMouseButtonPressed(VK_LBUTTON))
	{
		if (m_ActIsOnPtr->IsPointInActor(p))
		{
			return true;
			++m_HitCntr;
		}
	}
	return false;
}