#include "stdafx.h"
#include "BulletList.h"
#include "PolarStarBullet.h"
#include "MainGame.h"
#include "EnemyList.h"
#define GAME_ENGINE (GameEngine::GetSingleton())

BulletList::BulletList(EnemyList* enemyListPtr) : m_EnemyListPtr(enemyListPtr)
{
	for (int i = 0; i < NR_OF_MAX_BULLETS; ++i)
	{
		m_BulletPtrArr.push_back(nullptr);
	}
}

BulletList::~BulletList()
{
	for (size_t i = 0; i < m_BulletPtrArr.size(); ++i)
	{
		if (m_BulletPtrArr[i] != nullptr)
		{
			delete m_BulletPtrArr[i];
			m_BulletPtrArr[i] = nullptr;
		}
	}
}

void BulletList::Tick(double deltaTime, int direction)
{
	m_HeroDirection = direction;

	for (size_t i = 0; i < m_BulletPtrArr.size(); ++i)
	{
		if (m_BulletPtrArr[i] != nullptr)
		{
			m_BulletPtrArr[i]->GetActor()->AddContactListener(this);
		}
	}
	
	m_BulletTimer += deltaTime;
	ShootHandler();
	for (size_t i = 0; i < m_BulletPtrArr.size(); ++i)
	{
		if (m_BulletPtrArr[i] != nullptr)
		{
			m_BulletPtrArr[i]->Tick();
		}
	}
}

void BulletList::Remove(PolarStarBullet* ArrowPtr)
{
	for (size_t i = 0; i < m_BulletPtrArr.size(); i++)
	{
		if (m_BulletPtrArr[i] != nullptr)
		{
			delete m_BulletPtrArr[i];
			m_BulletPtrArr[i] = nullptr;
		}
	}
}

void BulletList::Paint()
{
	for (size_t i = 0; i < m_BulletPtrArr.size(); ++i)
	{
		if (m_BulletPtrArr[i] != nullptr)
		{
			m_BulletPtrArr[i]->Paint();
		}
	}
}

void BulletList::ShootHandler()
{
	m_HeroPos = MainGame::m_HeroPos;

	for (int i = 0; i < NR_OF_MAX_BULLETS; ++i)
	{
		if ((GAME_ENGINE->IsKeyboardKeyDown('J')) && (m_IsShootWorthy) && (m_BulletPtrArr[i] == nullptr))
		{
			m_BulletTimer = 0;
			m_IsShootWorthy = false;
			m_BulletPtrArr[i] = new PolarStarBullet(m_HeroPos, m_HeroDirection);
		}
		else if (!GAME_ENGINE->IsKeyboardKeyDown('J'))
		{
			m_IsShootWorthy = true;
		}
		if (m_BulletPtrArr[i] != nullptr)
		{
			if (m_BulletTimer >= 0.5)
			{
				delete m_BulletPtrArr[i];
				m_BulletPtrArr[i] = nullptr;
			}
		}
	}
}

void BulletList::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	for (size_t i = 0; i <m_BulletPtrArr.size(); i++)
	{
		if (m_EnemyListPtr->IsHit(actOtherPtr))
		{
			Remove(m_BulletPtrArr[i]);
		}
	}
}

void BulletList::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
}

void BulletList::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}