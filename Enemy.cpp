#include "stdafx.h"
#include "Enemy.h"
#include "Entity.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Enemy::Enemy(LevelOutdoor* level, Hero* hero, DOUBLE2 position) 
: m_LevelPtr(level), m_HeroPtr(hero), m_Position(position)
{
	Init();
}

void Enemy::Init()
{
	m_BitmapManager = new BitmapManager();
	m_BmpNpc1Ptr = m_BitmapManager->LoadBitmap(String("./Assets/Images/SpriteSheet_Npc03.png"));

	m_ActPtr = new PhysicsActor(m_Position, 0, BodyType::DYNAMIC);
	m_ActPtr->AddBoxShape(25, 40, 0, 1, 50);
	m_ActPtr->AddContactListener(this);
	m_ActPtr->SetFixedRotation(true);
}

Enemy::~Enemy()
{
	RemoveEnemy();
	delete m_BitmapManager;
	m_BitmapManager = nullptr;
}

void Enemy::Tick(double deltaTime)
{
	if (m_ActPtr != nullptr)
	{
		UpdateVariables(deltaTime);
		Entity::UpdateVariables(deltaTime);
		MoveTowardHero(deltaTime);
		Entity::ApplyImpulse(deltaTime);
	}
}

void Enemy::UpdateVariables(double deltaTime)
{
	m_BaseSpeed = 200;
	
	if (m_BoolDealDamage == false)
	{
		m_DamageTime += deltaTime;
	}
	if (m_DamageTime > 2)
	{
		m_BoolDealDamage = true;
		m_DamageTime = 0.0;
	}
}

void Enemy::Paint()
{
	if (m_ActPtr != nullptr)
	{
		CreateWorldMatrix();
		GAME_ENGINE->DrawBitmap(m_BmpNpc1Ptr, Rect());
	}
}

void Enemy::CreateWorldMatrix()
{
	DOUBLE2 actHeroPos = m_ActPtr->GetPosition();
	double actHeroAngle = m_ActPtr->GetAngle();

	MATRIX3X2 matPivot, matTransform, matTranslate, matAngle, matScale;
	matPivot.SetAsTranslate(DOUBLE2(-TILE_SIZE / 2, -TILE_SIZE / 2));
	matAngle.SetAsRotate(actHeroAngle);

	switch (m_Direction)
	{
	case Entity::Direction::LEFT:
		matScale.SetAsScale(1, 1);
		break;
	case Entity::Direction::RIGHT:
		matScale.SetAsScale(-1, 1);
		break;
	default:
		break;
	}

	matTranslate.SetAsTranslate(actHeroPos);
	matTransform = matPivot*matScale*matAngle*matTranslate;
	GAME_ENGINE->SetWorldMatrix(matTransform);
}

void Enemy::Anim()
{
	switch (m_ActionState)
	{
	case ActionState::IDLE:
		m_CurrentFrame = 2;
		break;
	case ActionState::WALK:
		if (m_AccuTime > 1.0 / WALK_FR_PER_SEC)
		{
			m_AccuTime = 0;
			m_CurrentFrame = ++m_CurrentFrame % WALK_FR;
		}
		break;
	case ActionState::ATTACK:
		if (m_AccuTime > 1.0 / ATT_FR_PER_SEC)
		{
			if (m_CurrentFrame > ATT_FR - 1) 
				m_CurrentFrame = 0;
			m_AccuTime = 0;
			m_CurrentFrame = ++m_CurrentFrame % ATT_FR;
		}
	default:
		break;
	}
}

RECT Enemy::Rect()
{
	RECT r;

	switch (m_ActionState)
	{
	case ActionState::IDLE:
		r.top = CLIP_SIZE * 0;
		break;
	case ActionState::WALK:
		r.top = CLIP_SIZE * 0;
		break;
	case ActionState::ATTACK:
		r.top = CLIP_SIZE * 1;
		break;
	default:
		break;
	}

	r.bottom = CLIP_SIZE + r.top;
	r.left = CLIP_SIZE * m_CurrentFrame;
	r.right = CLIP_SIZE + r.left;

	return r;
}

void Enemy::RemoveEnemy()
{
	if (m_ActPtr != nullptr)
	{
		delete m_ActPtr;
		m_ActPtr = nullptr;
	}
}

void Enemy::MoveTowardHero(double deltaTime)
{
	m_PosDif = m_ActPtr->GetPosition() - m_HeroPtr->GetPosition();
	if ((m_PosDif.x < 50) && (m_PosDif.x > -50) || (m_AttackWorthy))
	{
		m_AttackWorthy = true;
		m_MoveWorthy = false;
		Attack(deltaTime);
	}
	else if ((m_PosDif.x < 0) && (m_MoveWorthy))
	{
		MoveRight();
	}
	else if (m_PosDif.x < -MOVE_RANGE)
	{
		Idle();
	}
	else if ((m_PosDif.x < MOVE_RANGE) && (m_MoveWorthy))
	{
		MoveLeft();
	}
	else
	{
		Idle();
	}
}

void Enemy::Attack(double deltaTime)
{
	m_AttackTime += deltaTime;
	m_ActionState = ActionState::ATTACK;
	ResetCurrentFrame();
	Anim();
	if (m_AttackTime >= 0.5)
	{
		m_AttackTime = 0;
		m_MoveWorthy = true;
		m_AttackWorthy = false;
		if ((m_PosDif.x < 90) && (m_PosDif.x > -90))
		{
			DealDamage();
		}
	}
}

void Enemy::DealDamage()
{
	if (m_BoolDealDamage)
	{
		DamageHero::DealDamage(BASE_DAMAGE);
		m_BoolDealDamage = false;
	}
}

int Enemy::GetHealth()
{
	return m_Health;
}

int Enemy::GetDirection()
{
	int id = 3;
	switch (m_Direction)
	{
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

void Enemy::SetHealth(int health)
{
	m_Health -= health;
}

// ======== Collision ========												
void Enemy::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	if (actOtherPtr == m_HeroPtr->GetActor())
	{
		DealDamage();
	}
}

void Enemy::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
}

void Enemy::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{
}