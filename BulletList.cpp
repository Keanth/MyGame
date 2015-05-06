#include "stdafx.h"
#include "BulletList.h"
#include "PolarStarBullet.h"
#include "NightSpiritBullet.h"
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
	for (size_t i = 0; i < m_BulletPtrArr.size(); ++i)
	{
		if (m_BulletPtrArr[i] != nullptr)
		{
			m_BulletPtrArr[i]->GetActor()->AddContactListener(this);
		}
	}
	
	for (size_t i = 0; i < m_BulletPtrArr.size(); ++i)
	{
		if (m_BulletPtrArr[i] != nullptr)
		{
			m_BulletPtrArr[i]->Tick(deltaTime);
		}
	}

	RemoveFromList();
}

void BulletList::Remove(Projectile* ArrowPtr)
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

void BulletList::ShootHandler(Projectile* projectile)
{
	for (size_t i = 0; i < NR_OF_MAX_BULLETS; ++i)
	{
		if (m_BulletPtrArr[i] == nullptr)
		{
			m_BulletPtrArr[i] = projectile;
			break;
		}
	}
}

void BulletList::RemoveFromList()
{
	for (size_t i = 0; i < NR_OF_MAX_BULLETS; ++i)
	{
		if (m_BulletPtrArr[i] != nullptr)
		{
			if (m_BulletPtrArr[i]->Remove())
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
		if ((m_EnemyListPtr->IsHit(actOtherPtr)))
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