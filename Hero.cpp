#include "stdafx.h"
#include "Hero.h"
#include "Entity.h"

#include "PolarStarBullet.h"
#include "MyGame.h"
#include "MainGame.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

int Hero::m_health = INITIAL_HEALTH;

Hero::Hero()
{
	Init();
}

void Hero::Init()
{
	m_BaseSpeed = 250;

	m_BmpHeroPtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/SpriteSheet_Hero.png"));
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

Hero::~Hero()
{
}

void Hero::Tick(double deltaTime)
{
	UpdateVariables(deltaTime);
	Entity::UpdateVariables(deltaTime);
	if (m_Godmode == false)
	{
		UserInput(deltaTime);
	}
	UserInputGodMode(deltaTime);
	Entity::ApplyImpulse(deltaTime);
	Gone();
}

void Hero::UpdateVariables(double deltaTime)
{
	m_ActFeetPtr->SetPosition(
		DOUBLE2(m_ActPtr->GetPosition().x,
		m_ActPtr->GetPosition().y + 16)); // position of the feet, trial and error
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
	if (m_Godmode)
	{
		m_OnFloor = true;
		m_ActPtr->SetGravityScale(0);
		m_health = 99;
	}
}

void Hero::UserInput(double deltaTime)
{
	// x-axis movement
	if ((GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT)) &&
		(GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
		)
	{
		Idle();
	}
	else if (GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT))
	{
		MoveLeft();
	}
	else if (GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
	{
		MoveRight();
	}
	else if (GAME_ENGINE->IsKeyboardKeyDown(VK_UP))
	{
		Up();
	}
	else if ((GAME_ENGINE->IsKeyboardKeyDown(VK_DOWN)) && (m_OnFloor == false))
	{
		DownJump();
	}
	else if (GAME_ENGINE->IsKeyboardKeyDown(VK_DOWN))
	{
		Down();
	}
	else
	{
		Idle();
	}
	// y-axis movement
	if ((m_OnFloor) && (GAME_ENGINE->IsKeyboardKeyDown('W')))
	{
		StartJump();
	}
	if ((m_ActiveJump) && (!GAME_ENGINE->IsKeyboardKeyDown('W')))
	{
		StopJump();
		m_Jump_Time = 0;
	}
	if ((m_ActiveJump) && (m_Jump_Time > AIR_TIMER))
	{
		StopJump();
	}
	if ((m_BoosterActive) && (GAME_ENGINE->IsKeyboardKeyDown('W')))
	{
		StartBooster();
		m_BoosterTimer += deltaTime;
	}
	if ((m_BoosterActive) && (GAME_ENGINE->IsKeyboardKeyReleased('W')))
	{
		m_BoolBoosterTrail = false;
	}
	if (m_BoosterTimer > BOOSTER_TIMER)
	{
		StopBooster();
	}
	//Shooter
	if ((GAME_ENGINE->IsKeyboardKeyDown('X')) && (m_IsShootWorthy))
	{
		//m_BulletListPtr->ShootHandler(m_ActPtr->GetPosition(), GetDirection(), 0);
		m_BulletListPtr->ShootHandler(new PolarStarBullet(m_ActPtr->GetPosition(), GetDirection()));
		m_IsShootWorthy = false;
	}
	else if (!GAME_ENGINE->IsKeyboardKeyDown('X'))
	{
		m_IsShootWorthy = true;
	}	
}

void Hero::UserInputGodMode(double deltaTime)
{
	if (GAME_ENGINE->IsKeyboardKeyPressed('G'))
	{
		GodMode();
	}
	if (m_Godmode)
	{
		DOUBLE2 pos = m_ActPtr->GetPosition();
		int offset = 7;

		if ((GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT)) &&
			(GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
			)
		{
			m_ActPtr->SetPosition(DOUBLE2(pos.x, pos.y));
		}
		else if (GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT))
		{
			m_ActPtr->SetPosition(DOUBLE2(pos.x -= offset, pos.y));
			Entity::m_Direction = Entity::Direction::LEFT;
		}
		else if (GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
		{
			m_ActPtr->SetPosition(DOUBLE2(pos.x += offset, pos.y));
			Entity::m_Direction = Entity::Direction::RIGHT;
		}
		if ((GAME_ENGINE->IsKeyboardKeyDown(VK_UP)) &&
			(GAME_ENGINE->IsKeyboardKeyDown(VK_DOWN))
			)
		{
			m_ActPtr->SetPosition(DOUBLE2(pos.x, pos.y));
		}
		else if (GAME_ENGINE->IsKeyboardKeyDown(VK_UP))
		{
			m_ActPtr->SetPosition(DOUBLE2(pos.x, pos.y -= offset));
		}
		else if (GAME_ENGINE->IsKeyboardKeyDown(VK_DOWN))
		{
			m_ActPtr->SetPosition(DOUBLE2(pos.x, pos.y += offset));
		}
		else
		{
			m_ActPtr->SetPosition(DOUBLE2(pos.x, pos.y));
		}
	}

}

void Hero::Paint()
{
	Entity::Paint();
	GAME_ENGINE->DrawBitmap(m_BmpHeroPtr, Rect());
	BoosterTrail();
	GAME_ENGINE->SetColor(COLOR(255, 255, 255));
//	GAME_ENGINE->DrawString(String("WEAPON XP : " ) + String(PolarStarBullet::m_Exp), -20, -10);
}

void Hero::Up()
{
	m_ActionState = ActionState::UP;
	m_Direction = Direction::UP;
	Anim();
}

void Hero::Down()
{
	m_ActionState = ActionState::DOWN;
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

	if (GAME_ENGINE->IsKeyboardKeyReleased('W'))
	{
		m_BoosterActive = true;
	}

}

void Hero::DownJump()
{
	m_ActionState = ActionState::DOWNJUMP;
	m_Direction = Direction::DOWN;
	Anim();
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
	case Hero::ActionState::DOWN:
		m_CurrentFrame = 1;
		break;
	case Hero::ActionState::STARTJUMP:
		m_CurrentFrame = 0;
		break;
	case Hero::ActionState::STOPJUMP:
		m_CurrentFrame = 1;
		break;
	case Hero::ActionState::DOWNJUMP:
		m_CurrentFrame = 2;
		break;
	default:
		break;
	}
}

RECT Hero::Rect()
{
	RECT r;
	if (m_Godmode)
	{
		r.top = CLIP_SIZE * 3;
		r.left = 0;
		r.bottom = CLIP_SIZE + r.top;
		r.right = CLIP_SIZE + r.left;
	}
	else
	{
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
		case Hero::ActionState::DOWN:
			r.top = CLIP_SIZE * 2;
			break;
		case Hero::ActionState::STARTJUMP:
			r.top = CLIP_SIZE * 0;
			break;
		case Hero::ActionState::STOPJUMP:
			r.top = CLIP_SIZE * 0;
			break;
		case Hero::ActionState::DOWNJUMP:
			r.top = CLIP_SIZE * 2;
			break;
		default:
			break;
		}

		r.left = CLIP_SIZE * m_CurrentFrame;
		r.bottom = CLIP_SIZE + r.top;
		r.right = CLIP_SIZE + r.left;
	}
	
	return r;
}

void Hero::Gone()
{
	if (m_ActPtr->GetPosition().y > 6000)
	{
		m_health = 0;
	}
}

void Hero::GodMode()
{
	m_Godmode =! m_Godmode;

	if (m_Godmode)
	{
		m_ActPtr->SetGhost(true);
	}
	else if (!m_Godmode )
	{
		m_ActPtr->SetGhost(false);
	}

	if (m_GodPointer == 0)
	{
		m_CurrentHealth = m_health;
		m_GodPointer++;
	}
	else if (m_GodPointer == 1)
	{
		m_health = m_CurrentHealth;
		m_GodPointer--;
	}
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