#include "stdafx.h"
#include "NightSpirit.h"

NightSpirit::NightSpirit(LevelOutdoor* level, Hero* hero, DOUBLE2 position)
{
	Init(level, hero, position);
	EnemyBase::Init();
}

void NightSpirit::Init(LevelOutdoor* level, Hero* hero, DOUBLE2 position)
{
	m_LevelPtr = level;
	m_HeroPtr = hero;
	m_Position = position;

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
}

void NightSpirit::Paint()
{
	EnemyBase::Paint();
}

void NightSpirit::MoveTowardHero(double deltaTime)
{
	m_PosDif = m_ActPtr->GetPosition() - m_HeroPtr->GetPosition();
	int idleDif = 8;
	int attackDif = 200;

	if ((m_PosDif.y < idleDif) && (m_PosDif.y > -idleDif))
	{
		Idle();
	}

	else if ((m_PosDif.y < 0) && (m_MoveWorthy))
	{
		MoveDown();
	}
	else if (m_PosDif.y < -MOVE_RANGE_NIGHTSPIRIT)
	{
		Idle();
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
