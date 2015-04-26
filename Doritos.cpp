#include "stdafx.h"
#include "Doritos.h"
#include "MyGame.h"

#include "PolarStarBullet.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Doritos::Doritos(DOUBLE2 position, Hero* hero)
{
	m_HeroPtr = hero;

	CLIP_POS = DOUBLE2(0, 1);
	FR = 5;
	FR_PER_SEC = 10;

	m_ActPickUpPtr = new PhysicsActor(position, 0, BodyType::DYNAMIC);
	m_ActPickUpPtr->AddBoxShape(CLIP_SIZE / 2, CLIP_SIZE / 2, 0.9, 0.1);
	m_ActPickUpPtr->SetFixedRotation(true);
	m_ActPickUpPtr->AddContactListener(this);
	m_ActPickUpPtr->SetBullet(true);
}

Doritos::~Doritos()
{
}

void Doritos::Tick(double deltaTime)
{
	PickUpBase::Tick(deltaTime);
	m_ActorPosition = m_ActPickUpPtr->GetPosition();
}

void Doritos::Paint()
{
	PickUpBase::Paint();
}

// ======== Collision ========												
void Doritos::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	if (m_ActPickUpPtr != nullptr)
	{
		if (actOtherPtr == m_HeroPtr->GetActor())
		{
			m_Hit = true;
			PolarStarBullet::m_Exp += BASE_AMOUNT;
		}
	}
}

void Doritos::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
}

void Doritos::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{
}