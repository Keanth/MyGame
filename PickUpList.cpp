#include "stdafx.h"
#include "PickUpList.h"
#include "PickUpBase.h"
#include "Hero.h"
#include "DamageHero.h"
#include "MainGame.h"
#include "Doritos.h"

PickUpList::PickUpList(Hero* hero)
:m_HeroPtr(hero)
{
}


PickUpList::~PickUpList()
{
	RemoveAll();
}

bool PickUpList::Add(PickUpBase* pickUpPtr)
{
	bool foo = true;

	if (m_PickUpPtrArr.empty())
	{
		m_PickUpPtrArr.push_back(pickUpPtr);
	}
	else
	{
		for (size_t i = 0; i < m_PickUpPtrArr.size(); ++i)
		{
			if (m_PickUpPtrArr[i] == nullptr)
			{
				m_PickUpPtrArr[i] = pickUpPtr;
				foo = false;
			}
		}
		if (foo)
		{
			m_PickUpPtrArr.push_back(pickUpPtr);
		}
	}
	return foo;
}

void PickUpList::Remove()
{
	for (size_t i = 0; i < m_PickUpPtrArr.size(); ++i)
	{
		delete m_PickUpPtrArr[i];
		m_PickUpPtrArr[i] = nullptr;
	}
}

void PickUpList::RemoveAll()
{
	for (size_t i = 0; i < m_PickUpPtrArr.size(); ++i)
	{
		if (m_PickUpPtrArr[i] != nullptr)
		{
			delete m_PickUpPtrArr[i];
			m_PickUpPtrArr[i] = nullptr;
		}
	}
	m_PickUpPtrArr.clear();
}

void PickUpList::Tick(double deltaTime)
{
	for (size_t i = 0; i < m_PickUpPtrArr.size(); i++)
	{
		if (m_PickUpPtrArr[i] != nullptr)
		{
			m_PickUpPtrArr[i]->Tick(deltaTime);
		}
	}
	Hit();
}

void PickUpList::Paint()
{
	for (size_t i = 0; i < m_PickUpPtrArr.size(); i++)
	{
		if (m_PickUpPtrArr[i] != nullptr)
		{
			m_PickUpPtrArr[i]->Paint();
		}
	}
}

void PickUpList::Hit()
{
	for (size_t i = 0; i < m_PickUpPtrArr.size(); i++)
	{
		if ((m_PickUpPtrArr[i] != nullptr) && (m_PickUpPtrArr[i]->GetHit()))
		{
			m_PickUpPtrArr[i]->RemoveContactListener();
			delete m_PickUpPtrArr[i];
			m_PickUpPtrArr[i] = nullptr;
		}
	}
}