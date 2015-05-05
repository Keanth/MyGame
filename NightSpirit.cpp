#include "stdafx.h"
#include "NightSpirit.h"
#include "NightSpiritBullet.h"
#include "BulletList.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

NightSpirit::NightSpirit(LevelOutdoor* level, Hero* hero, DOUBLE2 position, BulletList* bulletList)
{
	Init(level, hero, position, bulletList);
	EnemyBase::Init();
}

void NightSpirit::Init(LevelOutdoor* level, Hero* hero, DOUBLE2 position, BulletList* bulletList)
{
	m_LevelPtr = level;
	m_HeroPtr = hero;
	m_Position = position;
	m_BulletListPtr = bulletList;

	m_BmpPtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/SpriteSheet_Npc02.png"));
	m_BaseSpeed = 200;
	m_ClipSize = 96;

	m_ActPtr = new PhysicsActor(m_Position, 0, BodyType::DYNAMIC);
	m_ActPtr->AddBoxShape(m_ClipSize, m_ClipSize, 0, 1, 50);
	m_ActPtr->AddContactListener(this);
	m_ActPtr->SetFixedRotation(true);
	m_ActPtr->SetGravityScale(0);
}

NightSpirit::~NightSpirit()
{
}

void NightSpirit::Tick(double deltaTime)
{
	if (m_ActPtr != nullptr)
	{
		UpdateVariables(deltaTime);
		Entity::UpdateVariables(deltaTime);
		MoveTowardHero(deltaTime);
		Entity::ApplyImpulse(deltaTime);
	}
	if (m_AttackSpanTimeWorthy)
	{
		m_AttackSpanTimer += deltaTime;
		if (m_AttackSpanTimer >= 5)
		{
			m_AttackSpanTimeWorthy = false;
			m_AttackSpan = true;
			m_AttackSpanTimer = 0;
		}
	}
}

void NightSpirit::Paint()
{
	EnemyBase::Paint();
	GAME_ENGINE->DrawString(String(m_AttackTime), -10, -10);
	GAME_ENGINE->DrawString(String(m_AttackSpanTimer), 0, 0);

}

void NightSpirit::MoveTowardHero(double deltaTime)
{
	m_PosDif = m_ActPtr->GetPosition() - m_HeroPtr->GetPosition();
	int idleDif = 20;
	int attackDif = 100;

	if (m_AttackSpan == false)
	{
		Idle();
	}
	else if ((m_PosDif.y < attackDif) && (m_PosDif.y > -attackDif) && (m_AttackSpan))
	{
		Attack(deltaTime);
	}
	else if (m_PosDif.y < -MOVE_RANGE_NIGHTSPIRIT)
	{
		Idle();
	}
	else if ((m_PosDif.y < 0) && (m_MoveWorthy))
	{
		MoveDown();
	}
	else if ((m_PosDif.x < MOVE_RANGE_NIGHTSPIRIT) && (m_MoveWorthy))
	{
		MoveUp();
	}
	else
	{
		Idle();
	}
}

void NightSpirit::Anim()
{
	switch (m_ActionState)
	{
	case ActionState::IDLE:
		if (m_AccuTime > 1.0 / WALK_FR_PER_SEC_NIGHTSPIRIT)
		{
			m_AccuTime = 0;
			m_CurrentFrame = ++m_CurrentFrame % WALK_FR_NIGHTSPIRIT;
		}
		break;
	case ActionState::WALK:
		if (m_AccuTime > 1.0 / WALK_FR_PER_SEC_NIGHTSPIRIT)
		{
			m_AccuTime = 0;
			m_CurrentFrame = ++m_CurrentFrame % WALK_FR_NIGHTSPIRIT;
		}
		break;
	case ActionState::ATTACK:
		if (m_AccuTime > 1.0 / ATT_FR_PER_SEC_NIGHTSPIRIT)
		{
			if (m_CurrentFrame > 1.0 / ATT_FR_NIGHTSPIRIT)
			{
				m_AccuTime = 0;
				m_CurrentFrame = ++m_CurrentFrame % ATT_FR_NIGHTSPIRIT;
			}
		}
	default:
		break;
	}
}

RECT NightSpirit::Rect()
{
	RECT r;

	switch (m_ActionState)
	{
	case ActionState::IDLE:
		r.top = m_ClipSize * 0;
		break;
	case ActionState::WALK:
		r.top = m_ClipSize * 0;
		break;
	case ActionState::ATTACK:
		r.top = m_ClipSize * 1;
		break;
	default:
		break;
	}

	r.bottom = m_ClipSize + r.top;
	r.left = m_ClipSize * m_CurrentFrame;
	r.right = m_ClipSize + r.left;

	return r;
}

void NightSpirit::Idle()
{
	m_ActionState = ActionState::IDLE;
	Anim();
	m_DesiredVel.y = m_Vel.y * 0.85;
}

void NightSpirit::Attack(double deltaTime)
{
	m_AttackTime += deltaTime;
	m_ActionState = ActionState::ATTACK;
	ResetCurrentFrame();
	Anim();
	Shoot();
	if (m_AttackTime >= 2)
	{
		m_AttackTime = 0;
		m_MoveWorthy = true;
		m_AttackSpan = false;
		m_AttackSpanTimeWorthy = true;
	}
}

void NightSpirit::Shoot()
{
//	m_BulletListPtr->ShootHandler(new NightSpiritBullet(DOUBLE2(m_ActPtr->GetPosition().x - 200, m_ActPtr->GetPosition().y), GetDirection()));
}