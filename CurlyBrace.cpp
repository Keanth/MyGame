#include "stdafx.h"
#include "CurlyBrace.h"
#include "Entity.h"

#include "PolarStarBullet.h"
#include "MyGame.h"
#include "MainGame.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

int CurlyBrace::m_health = INITIAL_HEALTH;

CurlyBrace::CurlyBrace()
{
	Init();
}

void CurlyBrace::Init()
{
	m_BaseSpeed = 250;

	m_BmpHeroPtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/SpriteSheet_Regular.png"));
	m_BmpBoosterTrailPtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/Sym.png"));

	m_ActPtr = new PhysicsActor(HERO_SPAWNPOINT, 0, BodyType::DYNAMIC);
	m_ActPtr->AddBoxShape(20, 28, 0, 0);
	m_ActPtr->SetBullet(true);

	m_ActFeetPtr = new PhysicsActor(HERO_SPAWNPOINT, 0, BodyType::DYNAMIC);

	m_ActFeetPtr->AddBoxShape(10, 5, 0); //feet
	m_ActFeetPtr->AddContactListener(this);
	m_ActFeetPtr->SetGravityScale(0);
	m_ActFeetPtr->SetTrigger(true);
	m_ActFeetPtr->SetBullet(true);

	m_ActPtr->SetFixedRotation(true);
	m_ActFeetPtr->SetFixedRotation(true);
}

CurlyBrace::~CurlyBrace()
{
}

void CurlyBrace::Tick(double deltaTime)
{
	if (RunSequence)
	{
		UpdateVariables(deltaTime);
		Entity::UpdateVariables(deltaTime);
		AiSequence();
		Entity::ApplyImpulse(deltaTime);
	}
}

void CurlyBrace::UpdateVariables(double deltaTime)
{
	m_ActPtr->SetGravityScale(1);
}

void CurlyBrace::Paint()
{
	if (RunSequence)
	{
		Entity::Paint();
		GAME_ENGINE->DrawBitmap(m_BmpHeroPtr, Rect());
		BoosterTrail();
	}
}

void CurlyBrace::StartJump()
{
	m_ActionState = ActionState::STARTJUMP;
	m_ActiveJump = true;
	Anim();
	if (m_OnFloor)
	{
		m_DesiredVel.y = -200;
	}
	m_ActPtr->SetGravityScale(0);
}

void CurlyBrace::StopJump()
{
	m_ActionState = ActionState::STOPJUMP;
	m_ActPtr->SetGravityScale(1);
	Anim();

	if (GAME_ENGINE->IsKeyboardKeyReleased('W'))
	{
		m_BoosterActive = true;
	}

}

void CurlyBrace::DownJump()
{
	m_ActionState = ActionState::DOWNJUMP;
	m_Direction = Direction::DOWN;
	Anim();
}

void CurlyBrace::StartBooster()
{
	m_BoolBoosterTrail = true;
	m_DesiredVel.y = -350;
	m_ActiveJump = false;
}

void CurlyBrace::StopBooster()
{
	m_BoolBoosterTrail = false;
	m_BoosterActive = false;
	m_BoosterTimer = 0;
	m_ActPtr->SetGravityScale(1);
}

void CurlyBrace::BoosterTrail()
{
	if (m_BoolBoosterTrail)
	{
		DOUBLE2 pos;
		pos.x = 8;
		pos.y = 30;

		if (m_AccuTime > 1.0 / BOOSTER_FR_PER_SEC)
		{
			m_AccuTime = 0;
			m_BoosterFrame = ++m_BoosterFrame % BOOSTER_FR;
		}

		RECT2 r;

		r.top = CLIP_SIZE * 3;
		r.bottom = (CLIP_SIZE / 2) + r.top;
		r.left = ((CLIP_SIZE / 2) * m_BoosterFrame) + (12 * (CLIP_SIZE / 2));
		r.right = (CLIP_SIZE / 2) + r.left;


		GAME_ENGINE->DrawBitmap(m_BmpBoosterTrailPtr, pos, r);
	}
}

void CurlyBrace::Anim()
{
	switch (m_ActionState)
	{
	case CurlyBrace::ActionState::IDLE:
		m_CurrentFrame = 1;
		break;
	case CurlyBrace::ActionState::WALK:
		if (m_AccuTime > 1.0 / WALK_FR_PER_SEC)
		{
			m_AccuTime = 0;
			m_CurrentFrame = ++m_CurrentFrame % WALK_FR;
		}
		break;
	case CurlyBrace::ActionState::UP:
		m_CurrentFrame = 2;
		break;
	case CurlyBrace::ActionState::DOWN:
		m_CurrentFrame = 1;
		break;
	case CurlyBrace::ActionState::STARTJUMP:
		m_CurrentFrame = 0;
		break;
	case CurlyBrace::ActionState::STOPJUMP:
		m_CurrentFrame = 1;
		break;
	case CurlyBrace::ActionState::DOWNJUMP:
		m_CurrentFrame = 2;
		break;
	default:
		break;
	}
}

RECT CurlyBrace::Rect()
{
	RECT r;

	switch (m_ActionState)
	{
	case CurlyBrace::ActionState::WALK:
		r.top = CLIP_SIZE * 0;
		break;
	case CurlyBrace::ActionState::IDLE:
		r.top = CLIP_SIZE * 0;
		break;
	case CurlyBrace::ActionState::UP:
		r.top = CLIP_SIZE * 1;
		break;
	case CurlyBrace::ActionState::DOWN:
		r.top = CLIP_SIZE * 2;
		break;
	case CurlyBrace::ActionState::STARTJUMP:
		r.top = CLIP_SIZE * 0;
		break;
	case CurlyBrace::ActionState::STOPJUMP:
		r.top = CLIP_SIZE * 0;
		break;
	case CurlyBrace::ActionState::DOWNJUMP:
		r.top = CLIP_SIZE * 2;
		break;
	default:
		break;
	}

	r.left = CLIP_SIZE * m_CurrentFrame;
	r.bottom = CLIP_SIZE + r.top;
	r.right = CLIP_SIZE + r.left;

	return r;
}

void CurlyBrace::AiSequence()
{
	if (AiSequenceOrder == 0)
	{
		m_OnFloor = true;
		MoveRight();
		if (m_ActPtr->GetPosition().x >= 850)
		{
			Idle();
		}
		if (m_ActionState == ActionState::IDLE)
		{
			StartBooster();
		}
		if (m_ActPtr->GetPosition().y <= 4500)
		{
			RunSequence = false;
		}
	}
}

// ======== Collision ========												
void CurlyBrace::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
}

void CurlyBrace::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
}

void CurlyBrace::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}