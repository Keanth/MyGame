#include "stdafx.h"
#include "EnemyBase.h"

#include "MyGame.h"
#include "PickUpList.h"
#include "EnemyList.h"
#include "MainGame.h"
#include "PickUpBase.h"
#include "Doritos.h"
#include "HealthUp.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
	RemoveEnemy();
}

void EnemyBase::Init()
{
}

void EnemyBase::Tick(double deltaTime)
{
}

void EnemyBase::UpdateVariables(double deltaTime)
{
	if (m_BoolDealDamage == false)
	{
		m_DamageTime += deltaTime;
	}
	if (m_DamageTime > 2)
	{
		m_BoolDealDamage = true;
		m_DamageTime = 0.0;
	}
}

void EnemyBase::Paint()
{
	if (m_ActPtr != nullptr)
	{
		CreateWorldMatrix();
		GAME_ENGINE->DrawBitmap(m_BmpPtr, Rect());
	}
}

void EnemyBase::CreateWorldMatrix()
{
	DOUBLE2 actHeroPos = m_ActPtr->GetPosition();
	double actHeroAngle = m_ActPtr->GetAngle();

	MATRIX3X2 matPivot, matTransform, matTranslate, matAngle, matScale;
	matPivot.SetAsTranslate(DOUBLE2(-m_ClipSize/2, -m_ClipSize/2));
	matAngle.SetAsRotate(actHeroAngle);

	switch (m_Direction)
	{
	case Entity::Direction::LEFT:
		matScale.SetAsScale(1, 1);
		break;
	case Entity::Direction::RIGHT:
		matScale.SetAsScale(-1, 1);
		break;
	default:
		break;
	}

	matTranslate.SetAsTranslate(actHeroPos);
	matTransform = matPivot*matScale*matAngle*matTranslate;
	GAME_ENGINE->SetWorldMatrix(matTransform);
}

void EnemyBase::RemoveEnemy()
{
	if (m_ActPtr != nullptr)
	{
		if (EnemyList::PickUpCount % 4 == 0)
		{
			MainGame::m_PickUpListPtr->Add(new HealthUp(m_ActPtr->GetPosition(), m_HeroPtr));
		}
		else
		{
			MainGame::m_PickUpListPtr->Add(new Doritos(m_ActPtr->GetPosition(), m_HeroPtr));
		}

		EnemyList::PickUpCount++;
		delete m_ActPtr;
		m_ActPtr = nullptr;
		delete m_ActFeetPtr;
		m_ActFeetPtr = nullptr;
	}
}

void EnemyBase::DealDamage()
{
	if (m_BoolDealDamage)
	{
		DamageHero::DealDamage(BASE_DAMAGE_GRAVEKEEPER);
		m_BoolDealDamage = false;
	}
}

int EnemyBase::GetDirection()
{
	int id = 3;
	switch (m_Direction)
	{
	case Entity::Direction::UP:
		id = 0;
		break;
	case Entity::Direction::DOWN:
		id = 1;
		break;
	case Entity::Direction::LEFT:
		id = 2;
		break;
	case Entity::Direction::RIGHT:
		id = 3;
		break;
	default:
		break;
	}
	return id;
}

void EnemyBase::SetHealth(int health)
{
	m_Health -= health;
}

// ======== Collision ========												
void EnemyBase::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	if (actOtherPtr == m_HeroPtr->GetActor())
	{
		DealDamage();
	}
	if ((actThisPtr == m_ActFeetPtr) && (actOtherPtr != m_ActPtr))
	{
		m_OnFloor = true;
	}
}

void EnemyBase::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	if ((actThisPtr == m_ActFeetPtr) && (actOtherPtr != m_ActPtr))
	{
		m_OnFloor = false;
	}
}

void EnemyBase::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{
}