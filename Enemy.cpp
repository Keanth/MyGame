#include "stdafx.h"
#include "Enemy.h"
#include "Hero.h"
#include "LevelOutdoor.h"
#include "DamageHero.h"
#include "BitmapManager.h"
#define GAME_ENGINE (GameEngine::GetSingleton())

Enemy::Enemy(LevelOutdoor* level, Hero* hero, DOUBLE2 position) 
: m_LevelPtr(level), m_HeroPtr(hero)
{
	m_BitmapManager = new BitmapManager();
	m_BmpNpc1Ptr = m_BitmapManager->LoadBitmap(String("./Assets/Images/SpriteSheet_Npc03.png"));

	m_ActEnemyPtr = new PhysicsActor(position, 0, BodyType::DYNAMIC);
	m_ActEnemyPtr->AddBoxShape(25, 40, 0, 1,50);
	m_ActEnemyPtr->AddContactListener(this);
	m_ActEnemyPtr->SetFixedRotation(true);
}

Enemy::~Enemy()
{
	delete m_BitmapManager;
	RemoveEnemy();
}

void Enemy::Tick(double deltaTime)
{
	if (m_ActEnemyPtr != nullptr)
	{
		UpdateVariables(deltaTime);
		MoveTowardHero(deltaTime);
		ApplyImpulse(deltaTime);
	}
}

void Enemy::UpdateVariables(double deltaTime)
{
	m_AccuTime += deltaTime;
	m_Vel = m_ActEnemyPtr->GetLinearVelocity();
	m_DesiredVel = DOUBLE2(0.0, m_ActEnemyPtr->GetLinearVelocity().y);
	m_Mass = m_ActEnemyPtr->GetMass();

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
	if (m_ActEnemyPtr != nullptr)
	{
		CreateWorldMatrix();
		GAME_ENGINE->DrawBitmap(m_BmpNpc1Ptr, Rect());
		GAME_ENGINE->DrawString(String(m_CurrentFrame), 0, 0);
	}
}

void Enemy::CreateWorldMatrix()
{
	DOUBLE2 actHeroPos = m_ActEnemyPtr->GetPosition();
	double actHeroAngle = m_ActEnemyPtr->GetAngle();

	MATRIX3X2 matPivot, matTransform, matTranslate, matAngle, matScale;
	matPivot.SetAsTranslate(DOUBLE2(-CLIP_SIZE / 2, -CLIP_SIZE / 2));
	matAngle.SetAsRotate(actHeroAngle);
	matScale.SetAsScale(m_Direction.x, m_Direction.y);
	matTranslate.SetAsTranslate(actHeroPos);
	matTransform = matPivot*matScale*matAngle*matTranslate;
	GAME_ENGINE->SetWorldMatrix(matTransform);
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

void Enemy::RemoveEnemy()
{
	if (m_ActEnemyPtr != nullptr)
	{
		m_ActEnemyPtr->RemoveContactListener(this);
		delete m_ActEnemyPtr;
		m_ActEnemyPtr = nullptr;
	}
}

void Enemy::Idle()
{
	m_ActionState = ActionState::IDLE;
	Anim();
	m_DesiredVel.x = m_Vel.x * 0.85;
}

void Enemy::MoveLeft()
{
	m_ActionState = ActionState::WALK;
	Anim();
	m_DesiredVel.x = -200;
	m_Direction = DOUBLE2(1, 1);
}

void Enemy::MoveRight()
{
	m_ActionState = ActionState::WALK;
	Anim();
	m_DesiredVel.x = 200;
	m_Direction = DOUBLE2(-1, 1);
}

void Enemy::MoveTowardHero(double deltaTime)
{
	m_PosDif = m_ActEnemyPtr->GetPosition() - m_HeroPtr->GetPosition();
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

void Enemy::ApplyImpulse(double deltaTime)
{
	DOUBLE2 deltaVel = m_DesiredVel - m_Vel;
	DOUBLE2 j = m_Mass * deltaVel / PhysicsActor::SCALE;
	m_ActEnemyPtr->ApplyLinearImpulse(j);
}

void Enemy::ResetCurrentFrame()
{
	if (m_BoolCurentFrame)
	{
		m_CurrentFrame = 0;
		m_BoolCurentFrame = false;
	}
}

//getters
PhysicsActor* Enemy::GetActor()
{
	return m_ActEnemyPtr;
}

int Enemy::GetHealth()
{
	return m_Health;
}

//setters
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