#include "stdafx.h"
#include "Entity.h"
#include "MainGame.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Entity::Entity()
{
}

Entity::~Entity()
{
	delete m_ActPtr;
	m_ActPtr = nullptr;
	delete m_ActFeetPtr;
	m_ActFeetPtr = nullptr;
}

// ==== PUBLIC METHODS ====
void Entity::Tick(double deltaTime)
{
	UpdateVariables(deltaTime);
	ApplyImpulse(deltaTime);
}

void Entity::Paint()
{
	CreateWorldMatrix();
}

void Entity::RemoveContactListener()
{
	if (m_ActPtr != nullptr)
	{
		m_ActPtr->RemoveContactListener(this);
	}
}

int GetHealth()
{
	return 0;
}

// ==== PROTECTED METHODS ====
void Entity::Init()
{

}

void Entity::UpdateVariables(double deltaTime)
{
	m_AccuTime += deltaTime;
	m_Vel = m_ActPtr->GetLinearVelocity();
	m_DesiredVel = DOUBLE2(0.0, m_ActPtr->GetLinearVelocity().y);
	m_Mass = m_ActPtr->GetMass();
}

void Entity::CreateWorldMatrix()
{
	DOUBLE2 actHeroPos = m_ActPtr->GetPosition();
	double actHeroAngle = m_ActPtr->GetAngle();

	MATRIX3X2 matPivot, matTransform, matTranslate, matAngle, matScale;
	matPivot.SetAsTranslate(DOUBLE2(-TILE_SIZE / 2, -TILE_SIZE / 2));
	matAngle.SetAsRotate(actHeroAngle);

	switch (m_Direction)
	{
	case Entity::Direction::LEFT:
		matScale.SetAsScale(-1, 1);
		break;
	case Entity::Direction::RIGHT:
		matScale.SetAsScale(1, 1);
		break;
	default:
		break;
	}

	matTranslate.SetAsTranslate(actHeroPos);
	matTransform = matPivot*matScale*matAngle*matTranslate;
	GAME_ENGINE->SetWorldMatrix(matTransform);
}

void Entity::Idle()
{
	m_ActionState = ActionState::IDLE;
	Anim();
	m_DesiredVel.x = m_Vel.x * 0.85;
}

void Entity::MoveLeft()
{
	if (m_OnFloor)m_ActionState = ActionState::WALK;
	Anim();
	m_Direction = Direction::LEFT;
	m_DesiredVel.x = -m_BaseSpeed;
}

void Entity::MoveRight()
{
	if (m_OnFloor)m_ActionState = ActionState::WALK;
	Anim();
	m_Direction = Direction::RIGHT;
	m_DesiredVel.x = m_BaseSpeed;
}

void Entity::MoveUp()
{
	Anim();
	m_Direction = Direction::UP;
	m_DesiredVel.y = -m_BaseSpeed;
}

void Entity::MoveDown()
{
	Anim();
	m_Direction = Direction::DOWN;
	m_DesiredVel.y = m_BaseSpeed;
}

void Entity::ApplyImpulse(double deltaTime)
{
	DOUBLE2 deltaVel = m_DesiredVel - m_Vel;
	DOUBLE2 j = m_Mass * deltaVel / PhysicsActor::SCALE;
	m_ActPtr->ApplyLinearImpulse(j);
}

void Entity::ResetCurrentFrame()
{
	if (m_BoolCurrentFrame)
	{
		m_CurrentFrame = 0;
		m_BoolCurrentFrame = false;
	}
}

int Entity::GetDirection()
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

void Entity::SetBulletList(BulletList* bulletList)
{
	m_BulletListPtr = bulletList;
}

void Entity::SetPause(int number)
{	
	if (m_ActPtr != nullptr)
	{
		DOUBLE2 pos = m_ActPtr->GetPosition();
		switch (number)
		{
		case 0:
			m_ActPtr->SetPosition(pos);
			m_ActPtr->SetLinearVelocity(DOUBLE2(0, 0));
			m_ActPtr->SetGravityScale(0);
			break;
		case 1:
			m_ActPtr->SetGravityScale(1);
			break;
		default:
			break;
		}
	}
}