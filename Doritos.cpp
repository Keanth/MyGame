#include "stdafx.h"
#include "Doritos.h"
#include "MyGame.h"

Doritos::Doritos(DOUBLE2 position)
{
	CLIP_POS = DOUBLE2(0, 1);
	FR = 5;
	FR_PER_SEC = 10;

	m_ActPickUpPtr = new PhysicsActor(position, 0, BodyType::DYNAMIC);
	m_ActPickUpPtr->AddBoxShape(CLIP_SIZE / 2, CLIP_SIZE / 2, 0.9, 0.1);
	m_ActPickUpPtr->SetFixedRotation(true);
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