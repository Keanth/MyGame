#include "stdafx.h"
#include "HealthUp.h"

#include "MyGame.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

HealthUp::HealthUp(DOUBLE2 position, Hero* hero)
{
	m_HeroPtr = hero;

	CLIP_POS = DOUBLE2(0, 5);
	FR = 2;
	FR_PER_SEC = 4;

	m_ActPickUpPtr = new PhysicsActor(position, 0, BodyType::DYNAMIC);
	m_ActPickUpPtr->AddBoxShape(CLIP_SIZE, CLIP_SIZE, 0, 0);
	m_ActPickUpPtr->SetFixedRotation(true);
	m_ActPickUpPtr->AddContactListener(this);
	m_ActPickUpPtr->SetBullet(true);
}

HealthUp::~HealthUp()
{
}

void HealthUp::Tick(double deltaTime)
{
	PickUpBase::Tick(deltaTime);
	m_ActorPosition = m_ActPickUpPtr->GetPosition();
}

void HealthUp::Paint()
{
	PickUpBase::Paint();
}

// ======== Collision ========												
void HealthUp::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	if (m_ActPickUpPtr != nullptr)
	{
		if (actOtherPtr == m_HeroPtr->GetActor())
		{
			m_Hit = true;
			m_HeroPtr->m_health += BASE_AMOUNT;
		}
	}
}

void HealthUp::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
}

void HealthUp::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{
}