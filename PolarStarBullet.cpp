#include "stdafx.h"
#include "PolarStarBullet.h"
#include "BitmapManager.h"
#define GAME_ENGINE (GameEngine::GetSingleton())

int PolarStarBullet::m_InstanceCounter = 0;

PolarStarBullet::PolarStarBullet(DOUBLE2 pos, int direction) :m_HeroPos(pos), m_Direction(direction)
{
	m_BitmapManager = new BitmapManager();
	m_BmpArrowPtr = m_BitmapManager->LoadBitmap(String("./Assets/Images/Bullet.png"));
	
	switch (m_Direction)
	{
	case 0:
		m_ActBulletPtr = new PhysicsActor(DOUBLE2(m_HeroPos.x + BULLET_OFFSET, m_HeroPos.y), 0, BodyType::DYNAMIC);
		m_ActBulletPtr->AddBoxShape(BULLET_HEIGHT, BULLET_WIDTH, 0);
		break;
	case 1:
		m_ActBulletPtr = new PhysicsActor(DOUBLE2(m_HeroPos.x, m_HeroPos.y), 0, BodyType::DYNAMIC);
		m_ActBulletPtr->AddBoxShape(BULLET_HEIGHT, BULLET_WIDTH, 0);
		break;
	case 2:
		m_ActBulletPtr = new PhysicsActor(DOUBLE2(m_HeroPos.x, m_HeroPos.y + BULLET_OFFSET), 0, BodyType::DYNAMIC);
		m_ActBulletPtr->AddBoxShape(BULLET_WIDTH, BULLET_HEIGHT, 0);
		break;
	case 3:
		m_ActBulletPtr = new PhysicsActor(DOUBLE2(m_HeroPos.x, m_HeroPos.y + BULLET_OFFSET), 0, BodyType::DYNAMIC);
		m_ActBulletPtr->AddBoxShape(BULLET_WIDTH, BULLET_HEIGHT, 0);
		break;
	default:
		break;
	}

	m_ActBulletPtr->SetGravityScale(0);
	m_ActBulletPtr->SetFixedRotation(true);
	m_ActBulletPtr->SetBullet(true);
	m_ActBulletPtr->SetTrigger(true);
}


PolarStarBullet::~PolarStarBullet()
{
	if (m_ActBulletPtr != nullptr)
	{
		delete m_ActBulletPtr;
		m_ActBulletPtr = nullptr;
	}

	delete m_BitmapManager;
}

void PolarStarBullet::Tick()
{
	DOUBLE2 Vel = m_ActBulletPtr->GetLinearVelocity();
	DOUBLE2 NewVel = DOUBLE2(0.0, 0.0);

	switch (m_Direction)
	{
	case 0:
		NewVel.y = -800;
		break;
	case 1:
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

void PolarStarBullet::Paint()
{
	DOUBLE2 actArrowPos = m_ActBulletPtr->GetPosition();

	MATRIX3X2 matPivot, matTransform, matTranslate, matRotation;
	matPivot.SetAsTranslate(DOUBLE2(-BULLET_WIDTH/2, -BULLET_HEIGHT*4));
	matTranslate.SetAsTranslate(actArrowPos);

	switch (m_Direction)
	{
	case 0:
		matRotation.SetAsRotate(M_PI / 2);
		break;
	case 1:
		matRotation.SetAsRotate((3 / 2) * M_PI);
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

	GAME_ENGINE->DrawBitmap(m_BmpArrowPtr);
}
