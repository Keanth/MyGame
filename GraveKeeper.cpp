#include "stdafx.h"
#include "GraveKeeper.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

GraveKeeper::GraveKeeper(LevelOutdoor* level, Hero* hero, DOUBLE2 position)
{
	Init(level, hero, position);
	EnemyBase::Init();
}

void GraveKeeper::Init(LevelOutdoor* level, Hero* hero, DOUBLE2 position)
{
	m_LevelPtr = level;
	m_HeroPtr = hero;
	m_Position = position;

	m_BmpPtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/SpriteSheet_Npc03.png"));
	m_BaseSpeed = 200;
	m_ClipSize = 48;

	m_ActPtr = new PhysicsActor(m_Position, 0, BodyType::DYNAMIC);
	m_ActPtr->AddBoxShape(m_ClipSize, m_ClipSize, 0, 1, 50);
	m_ActPtr->AddContactListener(this);
	m_ActPtr->SetFixedRotation(true);

	m_ActFeetPtr = new PhysicsActor(m_Position, 0, BodyType::DYNAMIC);
	m_ActFeetPtr->AddBoxShape(10, 2, 0); //feet
	m_ActFeetPtr->AddContactListener(this);
	m_ActFeetPtr->SetGravityScale(0);
	m_ActFeetPtr->SetTrigger(true);
	m_ActFeetPtr->SetBullet(true);
	m_ActFeetPtr->SetFixedRotation(true);
}

GraveKeeper::~GraveKeeper()
{
}

void GraveKeeper::Tick(double deltaTime)
{
	if (m_ActPtr != nullptr)
	{
		EnemyBase::UpdateVariables(deltaTime);
		UpdateVariables(deltaTime);
		Entity::UpdateVariables(deltaTime);
		MoveTowardHero(deltaTime);
		Entity::ApplyImpulse(deltaTime);
	}
}

void GraveKeeper::UpdateVariables(double deltaTime)
{
	m_ActFeetPtr->SetPosition(
		DOUBLE2(m_ActPtr->GetPosition().x,
		m_ActPtr->GetPosition().y + 22));
}

void GraveKeeper::Paint()
{
	EnemyBase::Paint();
}

void GraveKeeper::MoveTowardHero(double deltaTime)
{
	m_PosDif = m_ActPtr->GetPosition() - m_HeroPtr->GetPosition();
	int idleDif = 8;
	int attackDif = 50;

	if ((m_PosDif.x < idleDif) && (m_PosDif.x > -idleDif))
	{
		Idle();
	}
	else if (((m_PosDif.x < attackDif) && (m_PosDif.x > -attackDif) &&
		(m_PosDif.y < attackDif) && (m_PosDif.y > -attackDif)) || (m_AttackWorthy))
	{
		m_AttackWorthy = true;
		m_MoveWorthy = false;
		Attack(deltaTime);
	}
	else if ((m_PosDif.x < 0) && (m_MoveWorthy))
	{
		MoveRight();
	}
	else if (m_PosDif.x < -MOVE_RANGE_GRAVEKEEPER)
	{
		Idle();
	}
	else if ((m_PosDif.x < MOVE_RANGE_GRAVEKEEPER) && (m_MoveWorthy))
	{
		MoveLeft();
	}
	else
	{
		Idle();
	}
}