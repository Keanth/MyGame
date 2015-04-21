#include "stdafx.h"
#include "HealthUp.h"
#include "Hero.h"
#include "MyGame.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

HealthUp::HealthUp(DOUBLE2 position)
{
	m_ActPickUpPtr = new PhysicsActor(position, 0, BodyType::DYNAMIC);
	m_ActPickUpPtr->AddBoxShape(CLIP_SIZE, CLIP_SIZE, 0, 0);
}

HealthUp::~HealthUp()
{
	delete m_ActPickUpPtr;
	delete m_BmpPickUpPtr;
}

void HealthUp::Tick(double deltaTime)
{
	PickUpBase::Tick(deltaTime);
}

void HealthUp::Paint()
{
	PickUpBase::Paint();
}
