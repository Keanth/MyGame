#include "stdafx.h"
#include "Hero.h"
#include "LevelOutdoor.h"
#include "PolarStarBullet.h"
#include "BitmapManager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

int Hero::m_health = INITIAL_HEALTH;
const double Hero::AIR_TIMER = 2;

Hero::Hero()
{
	m_BitmapManager = new BitmapManager();
	m_BmpHeroPtr = m_BitmapManager->LoadBitmap(String("./Assets/Images/SpriteSheet_Hero.png"));

	m_ActHeroPtr = new PhysicsActor(HERO_SPAWNPOINT, 0, BodyType::DYNAMIC);
	//m_ActHeroPtr->AddCircleShape(10, DOUBLE2(0, -CLIP_SIZE / 3), 0, 0); //head
	//m_ActHeroPtr->AddBoxShape(10, 30, 0); //body
	m_ActHeroPtr->AddBoxShape(20, 28, 0, 0);

	m_ActHeroFeetPtr = new PhysicsActor(HERO_SPAWNPOINT, 0, BodyType::DYNAMIC);
	m_ActHeroFeetPtr->AddBoxShape(10, 2, 0); //feet
	m_ActHeroFeetPtr->AddContactListener(this);
	m_ActHeroFeetPtr->SetGravityScale(0);
	m_ActHeroFeetPtr->SetTrigger(true);

	m_ActHeroPtr->SetFixedRotation(true);
	m_ActHeroFeetPtr->SetFixedRotation(true);
}

Hero::~Hero()
{
	delete m_BitmapManager;
	delete m_ActHeroPtr;
	delete m_ActHeroFeetPtr;
}

void Hero::Tick(double deltaTime)
{
	UpdateVariables(deltaTime);
	UserInput(deltaTime);
	ApplyImpulse(deltaTime);
}

void Hero::UpdateVariables(double deltaTime)
{
	m_ActHeroFeetPtr->SetPosition(
		DOUBLE2(m_ActHeroPtr->GetPosition().x,
		m_ActHeroPtr->GetPosition().y + 15)); // position of the feet, trial and error

	m_AccuTime += deltaTime;
	m_Vel = m_ActHeroPtr->GetLinearVelocity();
	m_DesiredVel = DOUBLE2(0.0, m_ActHeroPtr->GetLinearVelocity().y);
	m_Mass = m_ActHeroPtr->GetMass();

	if (m_OnFloor)
	{
		m_BoostActive = false;
		m_ActiveJump = false;
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
	if (GAME_ENGINE->IsKeyboardKeyDown(VK_SPACE))
	{
		StartJump();
		m_Jump_Time += deltaTime;
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
}

void Hero::Paint()
{
	CreateWorldMatrix();
	GAME_ENGINE->DrawBitmap(m_BmpHeroPtr, Rect());
}

void Hero::CreateWorldMatrix()
{
	DOUBLE2 actHeroPos = m_ActHeroPtr->GetPosition();
	double actHeroAngle = m_ActHeroPtr->GetAngle();

	MATRIX3X2 matPivot, matTransform, matTranslate, matAngle, matScale;
	matPivot.SetAsTranslate(DOUBLE2(-CLIP_SIZE / 2, -CLIP_SIZE / 2));
	matAngle.SetAsRotate(actHeroAngle);
	
	switch (m_Direction)
	{
	case Hero::Direction::LEFT:
		matScale.SetAsScale(-1, 1);
		break;
	case Hero::Direction::RIGHT:
		matScale.SetAsScale(1, 1);
		break;
	default:
		break;
	}

	matTranslate.SetAsTranslate(actHeroPos);
	matTransform = matPivot*matScale*matAngle*matTranslate;
	GAME_ENGINE->SetWorldMatrix(matTransform);
}

void Hero::Idle()
{
	m_ActionState = ActionState::IDLE;
	Anim();
	m_DesiredVel.x = m_Vel.x * 0.85;
}

void Hero::MoveLeft()
{
	if (m_OnFloor)m_ActionState = ActionState::WALK;
	Anim();
	m_Direction = Direction::LEFT;
	m_DesiredVel.x = -250;
}

void Hero::MoveRight()
{
	if (m_OnFloor)m_ActionState = ActionState::WALK;
	Anim();
	m_Direction = Direction::RIGHT;
	m_DesiredVel.x = 250;
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
	m_Active = true;
	m_ActiveJump = true;
	m_BoostActive = true;
	Anim();
	if (m_OnFloor)
	{
		m_DesiredVel.y = -200;
	}
	if (m_Active = true)
	{
		m_ActHeroPtr->SetGravityScale(0);
	}
}

void Hero::StopJump()
{
	m_ActionState = ActionState::STOPJUMP;
	m_Active = false;
	m_BoostActive = true;
	m_ActHeroPtr->SetGravityScale(1);
	Anim();
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

	r.bottom = CLIP_SIZE + r.top;
	r.left = CLIP_SIZE * m_CurrentFrame;
	r.right = CLIP_SIZE + r.left;

	return r;
}

void Hero::ApplyImpulse(double deltaTime)
{
	DOUBLE2 deltaVel = m_DesiredVel - m_Vel;
	DOUBLE2 j = m_Mass * deltaVel / PhysicsActor::SCALE;
	m_ActHeroPtr->ApplyLinearImpulse(j);
}

int Hero::GetDirection()
{
	int id = 3;
	switch (m_Direction)
	{
	case Hero::Direction::UP:
		id = 0;
		break;
	case Hero::Direction::DOWN:
		id = 1;
		break;
	case Hero::Direction::LEFT:
		id = 2;
		break;
	case Hero::Direction::RIGHT:
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
	if (actThisPtr == m_ActHeroFeetPtr)
	{
		m_OnFloor = true;
	}
}

void Hero::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	if (actThisPtr == m_ActHeroFeetPtr)
	{
		m_OnFloor = false;
	}
}

void Hero::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}