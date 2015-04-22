#include "stdafx.h"
#include "Doritos.h"
#include "MyGame.h"
#include "DamageHero.h"

Doritos::Doritos(DOUBLE2 position, PhysicsActor* hero)
{
	CLIP_POS = DOUBLE2(0, 1);
	FR = 5;
	FR_PER_SEC = 10;
	m_ActHeroPtr = hero;

	m_ActPickUpPtr = new PhysicsActor(position, 0, BodyType::DYNAMIC);
	m_ActPickUpPtr->AddBoxShape(CLIP_SIZE / 2, CLIP_SIZE / 2, 0.9, 0.1);
	m_ActPickUpPtr->SetFixedRotation(true);
	m_ActPickUpPtr->AddContactListener(this);
}

Doritos::~Doritos()
{

}

void Doritos::Tick(double deltaTime)
{
	PickUpBase::Tick(deltaTime);
	m_ActorPosition = m_ActPickUpPtr->GetPosition();
//	Hit();
}

void Doritos::Paint()
{
	PickUpBase::Paint();
}

void Doritos::Hit()
{
	if (m_Hit)
	{
		DamageHero::DealDamage(10);
	}
}