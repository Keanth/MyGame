#include "stdafx.h"
#include "HealthUp.h"


#define GAME_ENGINE (GameEngine::GetSingleton())

HealthUp::HealthUp(DOUBLE2 position)
{
	CLIP_POS = DOUBLE2(2, 4);
	FR = 2;
	FR_PER_SEC = 4;

	m_ActPickUpPtr = new PhysicsActor(position, 0, BodyType::DYNAMIC);
	m_ActPickUpPtr->AddBoxShape(CLIP_SIZE, CLIP_SIZE, 0, 0);
	m_ActPickUpPtr->SetFixedRotation(true);
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