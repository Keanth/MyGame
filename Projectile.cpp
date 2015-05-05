#include "stdafx.h"
#include "Projectile.h"
#include "BitmapManager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

const double Projectile::DEFAULT_BULLET_DESPAWN_TIME = 0.5;

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
	if (m_ActBulletPtr != nullptr)
	{
		delete m_ActBulletPtr;
		m_ActBulletPtr = nullptr;
	}
}

void Projectile::Init()
{
	switch (m_Direction)
	{
	case 0:
		m_ActBulletPtr = new PhysicsActor(DOUBLE2(m_HeroPos.x + BULLET_OFFSET, m_HeroPos.y), 0, BodyType::DYNAMIC);
		break;
	case 1:
		m_ActBulletPtr = new PhysicsActor(DOUBLE2(m_HeroPos.x, m_HeroPos.y), 0, BodyType::DYNAMIC);
		break;
	case 2:
		m_ActBulletPtr = new PhysicsActor(DOUBLE2(m_HeroPos.x, m_HeroPos.y + BULLET_OFFSET), 0, BodyType::DYNAMIC);
		break;
	case 3:
		m_ActBulletPtr = new PhysicsActor(DOUBLE2(m_HeroPos.x, m_HeroPos.y + BULLET_OFFSET), 0, BodyType::DYNAMIC);
		break;
	default:
		break;
	}
	m_ActBulletPtr->AddBoxShape(BULLET_HIT_REGION, BULLET_HEIGHT, 0);
	m_ActBulletPtr->SetGravityScale(0);
	m_ActBulletPtr->SetFixedRotation(true);
	m_ActBulletPtr->SetBullet(true);
	m_ActBulletPtr->SetTrigger(true);
}

void Projectile::Tick(double deltaTime)
{
	m_BulletTimer += deltaTime;

	DOUBLE2 Vel = m_ActBulletPtr->GetLinearVelocity();
	DOUBLE2 NewVel = DOUBLE2(0.0, 0.0);

	switch (m_Direction)
	{
	case 0:
		NewVel.y = -800;
		break;
	case 1:
		NewVel.y = 800;
		break;
	case 2:
		NewVel.x = -800;
		break;
	case 3:
		NewVel.x = 800;
		break;
	default:
		break;
	}

	double mass = m_ActBulletPtr->GetMass();

	DOUBLE2 j = mass * (NewVel - Vel) / PhysicsActor::SCALE;
	m_ActBulletPtr->ApplyLinearImpulse(j);
}

void Projectile::Paint()
{
	CreateMatrix();
	GAME_ENGINE->DrawBitmap(m_BmpArrowPtr);
}

void Projectile::CreateMatrix()
{
	DOUBLE2 actArrowPos = m_ActBulletPtr->GetPosition();

	MATRIX3X2 matPivot, matTransform, matTranslate, matRotation;
	matPivot.SetAsTranslate(DOUBLE2(-BULLET_WIDTH / 2, -BULLET_HEIGHT * 4));
	matTranslate.SetAsTranslate(actArrowPos);

	switch (m_Direction)
	{
	case 0:
		matRotation.SetAsRotate(M_PI / 2);
		break;
	case 1:
		matRotation.SetAsRotate(M_PI / 2);
		break;
	case 2:
		matRotation.SetAsRotate(M_PI);
		break;
	case 3:
		matRotation.SetAsRotate(0);
		break;
	default:
		break;
	}

	matTransform = matPivot * matRotation * matTranslate;
	GAME_ENGINE->SetWorldMatrix(matTransform);
}

bool Projectile::Remove()
{
	if (m_BulletTimer >= m_BulletDespawnTime)
	{
		return true;
	}
	return false;
}