#include "stdafx.h"
#include "EnemyList.h"
#include "Enemy.h"
#include "BulletList.h"
#include "PickUpList.h"
#include "MainGame.h"
#include "Doritos.h"
#define GAME_ENGINE (GameEngine::GetSingleton())

EnemyList::EnemyList(Hero* hero)
:m_HeroPtr(hero)
{

}

EnemyList::~EnemyList()
{
	RemoveAll();
}

bool EnemyList::Add(Enemy* enemyPtr)
{
	bool foo = true;

	if (m_EnemyPtrArr.empty())
	{
		m_EnemyPtrArr.push_back(enemyPtr);
	}
	else
	{
		for (size_t i = 0; i < m_EnemyPtrArr.size(); ++i)
		{
			if (m_EnemyPtrArr[i] == nullptr)
			{
				m_EnemyPtrArr[i] = enemyPtr;
				foo = false;
			}
		}
		if (foo)
		{
			m_EnemyPtrArr.push_back(enemyPtr);
		}
	}
	return foo;
}

bool EnemyList::Remove(Enemy* enemyPtr)
{
	for (size_t i = 0; i < m_EnemyPtrArr.size(); ++i)
	{
		if (m_EnemyPtrArr[i] == enemyPtr)
		{
			delete m_EnemyPtrArr[i];
			m_EnemyPtrArr[i] = nullptr;
			return true;
		}

	}
	return false;
}

void EnemyList::RemoveAll()
{
	for (size_t i = 0; i < m_EnemyPtrArr.size(); ++i)
	{
		if (m_EnemyPtrArr[i] != nullptr)
		{
			m_EnemyPtrArr[i]->RemoveContactListener();
			delete m_EnemyPtrArr[i];
			m_EnemyPtrArr[i] = nullptr;
		}
	}
	m_EnemyPtrArr.clear();
}

void EnemyList::Tick(double deltaTime)
{
	for (size_t i = 0; i < m_EnemyPtrArr.size(); i++)
	{
		if (m_EnemyPtrArr[i] != nullptr)
		{
			m_EnemyPtrArr[i]->Tick(deltaTime);
		}
	}
	
	HeDead();
}

void EnemyList::Paint()
{
	for (size_t i = 0; i < m_EnemyPtrArr.size(); i++)
	{
		if (m_EnemyPtrArr[i] != nullptr)
		{
			m_EnemyPtrArr[i]->Paint();
		}
	}
}

bool EnemyList::IsHit(PhysicsActor* actOtherPtr)
{
	for (size_t i = 0; i < m_EnemyPtrArr.size(); i++)
	{
		if (m_EnemyPtrArr[i]->GetActor() != nullptr)
		{
			if (m_EnemyPtrArr[i]->GetActor() == actOtherPtr)
			{
				m_EnemyPtrArr[i]->SetHealth(3);
				return true;
			}
		}
	}
	return false;
}

int EnemyList::GetSize()
{
	int size= 0;
	for (size_t i = 0; i < m_EnemyPtrArr.size(); i++)
	{
		if (m_EnemyPtrArr[i] != nullptr)
		{
			++size;
		}
	}
	return size;
}

void EnemyList::HeDead()
{
	for (size_t i = 0; i < m_EnemyPtrArr.size(); i++)
	{
		if (m_EnemyPtrArr[i] != nullptr)
		{
			if (m_EnemyPtrArr[i]->GetHealth() <= 0)
			{
				m_EnemyPtrArr[i]->RemoveEnemy();
			}
		}
	}
}