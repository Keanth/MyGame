#include "stdafx.h"
#include "Hero.h"
#include "Entity.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

int Hero::m_health = INITIAL_HEALTH;

Hero::Hero()
{
	Init();
}

void Hero::Init()
{
	m_BaseSpeed = 250;

	m_BitmapManager = new BitmapManager();
	m_BmpHeroPtr = m_BitmapManager->LoadBitmap(String("./Assets/Images/SpriteSheet_Hero.png"));

	m_ActPtr = new PhysicsActor(HERO_SPAWNPOINT, 0, BodyType::DYNAMIC);
	m_ActPtr->AddBoxShape(20, 28, 0, 0);
	m_ActPtr->SetBullet(true);

	m_ActFeetPtr = new PhysicsActor(HERO_SPAWNPOINT, 0, BodyType::DYNAMIC);

	m_ActFeetPtr->AddBoxShape(10, 2, 0); //feet
	m_ActFeetPtr->AddContactListener(this);
	m_ActFeetPtr->SetGravityScale(0);
	m_ActFeetPtr->SetTrigger(true);
	m_ActFeetPtr->SetBullet(true);

	m_ActPtr->SetFixedRotation(true);
	m_ActFeetPtr->SetFixedRotation(true);

	m_BmpBoosterTrailPtr = m_BitmapManager->LoadBitmapW(String("./Assets/Images/Sym.png"));
}

Hero::~Hero()
{
	delete m_ActFeetPtr;
	m_ActFeetPtr = nullptr;
	delete m_BitmapManager;
	m_BitmapManager = nullptr;
}

void Hero::Tick(double deltaTime)
{
	UpdateVariables(deltaTime);
	Entity::UpdateVariables(deltaTime);
	UserInput(deltaTime);
	Entity:ApplyImpulse(deltaTime);
}

void Hero::UpdateVariables(double deltaTime)
{
	m_ActFeetPtr->SetPosition(
		DOUBLE2(m_ActPtr->GetPosition().x,
		m_ActPtr->GetPosition().y + 14)); // position of the feet, trial and error
	if (m_OnFloor)
	{
		m_BoosterActive = false;
		m_ActiveJump = false;
		m_BoosterFrame = 0;
		StopBooster();
	}
	if (m_ActiveJump)
	{
		m_Jump_Time += deltaTime;
	}
}

void Hero::UserInput(double deltaTime)
{
	// x-axis movement
	if ((GAME_ENGINE->IsKeyboardKeyDown('Q')) &&
		(GAME_ENGINE->IsKeyboardKeyDown('D'))
		)
	{
		Idle();
	}
	else if (GAME_ENGINE->IsKeyboardKeyDown('Q'))
	{
		MoveLeft();
	}
	else if (GAME_ENGINE->IsKeyboardKeyDown('D'))
	{
		MoveRight();
	}
	else if (GAME_ENGINE->IsKeyboardKeyDown('Z'))
	{
		Up();
	}
	else
	{
		Idle();
	}
	// y-axis movement
	if ((m_OnFloor) && (GAME_ENGINE->IsKeyboardKeyDown(VK_SPACE)))
	{
		StartJump();
	}
	if ((m_ActiveJump) && (!GAME_ENGINE->IsKeyboardKeyDown(VK_SPACE)))
	{
		StopJump();
		m_Jump_Time = 0;
	}
	if ((m_ActiveJump) && (m_Jump_Time > AIR_TIMER))
	{
		StopJump();
	}
	if ((m_BoosterActive) && (GAME_ENGINE->IsKeyboardKeyDown(VK_SPACE)))
	{
		StartBooster();
		m_BoosterTimer += deltaTime;
	}
	if ((m_BoosterActive) && (GAME_ENGINE->IsKeyboardKeyReleased(VK_SPACE)))
	{
		m_BoolBoosterTrail = false;
	}
	if (m_BoosterTimer > BOOSTER_TIMER)
	{
		StopBooster();
	}
}

void Hero::Paint()
{
	Entity::Paint();
	GAME_ENGINE->DrawBitmap(m_BmpHeroPtr, Rect());
	BoosterTrail();
}

void Hero::Up()
{
	m_ActionState = ActionState::UP;
	m_Direction = Direction::UP;
	Anim();
}

void Hero::StartJump()
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

void Hero::StopJump()
{
	m_ActionState = ActionState::STOPJUMP;
	m_ActPtr->SetGravityScale(1);
	Anim();

	if (GAME_ENGINE->IsKeyboardKeyReleased(VK_SPACE))
	{
		m_BoosterActive = true;
	}

}

void Hero::StartBooster()
{
	m_BoolBoosterTrail = true;
	m_DesiredVel.y = -350;
	m_ActiveJump = false;
}

void Hero::StopBooster()
{
	m_BoolBoosterTrail = false;
	m_BoosterActive = false;
	m_BoosterTimer = 0;
	m_ActPtr->SetGravityScale(1);
}

void Hero::BoosterTrail()
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

void Hero::Anim()
{
	switch (m_ActionState)
	{
	case Hero::ActionState::IDLE:
		m_CurrentFrame = 1;
		break;
	case Hero::ActionState::WALK:
		if (m_AccuTime > 1.0 / WALK_FR_PER_SEC)
		{
			m_AccuTime = 0;
			m_CurrentFrame = ++m_CurrentFrame % WALK_FR;
		}
		break;
	case Hero::ActionState::UP:
		m_CurrentFrame = 2;
		break;
	case Hero::ActionState::STARTJUMP:
		m_CurrentFrame = 0;
		break;
	case Hero::ActionState::STOPJUMP:
		m_CurrentFrame = 1;
		break;
	default:
		break;
	}
}

RECT Hero::Rect()
{
	RECT r;

	switch (m_ActionState)
	{
	case Hero::ActionState::WALK:
		r.top = CLIP_SIZE * 0;
		break;
	case Hero::ActionState::IDLE:
		r.top = CLIP_SIZE * 0;
		break;
	case Hero::ActionState::UP:
		r.top = CLIP_SIZE * 1;
		break;
	case Hero::ActionState::STARTJUMP:
		r.top = CLIP_SIZE * 0;
		break;
	case Hero::ActionState::STOPJUMP:
		r.top = CLIP_SIZE * 0;
		break;
	default:
		break;
	}

	r.left = CLIP_SIZE * m_CurrentFrame;
	r.bottom = CLIP_SIZE + r.top;
	r.right = CLIP_SIZE + r.left;

	return r;
}

void Hero::Gone()
{
	if (m_ActPtr->GetPosition().y > 6000)
	{
		m_health = 0;
	}
}

int Hero::GetDirection()
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

// ======== Collision ========												
void Hero::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	if ((actThisPtr == m_ActFeetPtr) && (actOtherPtr != m_ActPtr))
	{
		m_OnFloor = true;
	}
}

void Hero::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	if ((actThisPtr == m_ActFeetPtr) && (actOtherPtr != m_ActPtr))
	{
		m_OnFloor = false;
	}
}

void Hero::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}