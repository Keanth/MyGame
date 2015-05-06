#include "stdafx.h"
#include "Hero.h"
#define GAME_ENGINE (GameEngine::GetSingleton())
Hero::Hero()
{
	m_BmpHeroPtr = new Bitmap(String("./Assets/Images/Player1_Level01_SpriteSheet.png"));
	m_ActHeroPtr = new PhysicsActor(DOUBLE2(200, 200), 0, BodyType::DYNAMIC);
	/*m_ActHeroPtr->AddCircleShape(40);
	m_ActHeroPtr->AddBoxShape(60, 65);*/
	m_ActHeroPtr->AddBoxShape(CLIP_WIDTH, CLIP_HEIGHT, 0);
	m_ActHeroPtr->AddContactListener(this);
	m_ActHeroPtr->SetFixedRotation(true);
}

Hero::~Hero()
{
	delete m_BmpHeroPtr;
	delete m_ActHeroPtr;
}

void Hero::Tick(double deltaTime)
{
	m_AccuTime += deltaTime;
	m_Vel = m_ActHeroPtr->GetLinearVelocity();
	m_NewVel = DOUBLE2(0.0, m_ActHeroPtr->GetLinearVelocity().y);
	m_Mass = m_ActHeroPtr->GetMass();

	Idle();
	Move();
	Jump();
	Attack();

	ApplyImpulse();
}

void Hero::Paint()
{
	DOUBLE2 actHeroPos = m_ActHeroPtr->GetPosition();
	double actHeroAngle = m_ActHeroPtr->GetAngle();

	MATRIX3X2 matPivot, matTransform, matTranslate, matAngle, matScale;
	matPivot.SetAsTranslate(-CLIP_WIDTH / 2, -CLIP_HEIGHT / 2);
	matAngle.SetAsRotate(actHeroAngle);
	matScale.SetAsScale(m_HeroScale.x, m_HeroScale.y);
	matTranslate.SetAsTranslate(actHeroPos);
	matTransform = matPivot*matScale*matAngle*matTranslate;

	GAME_ENGINE->SetWorldMatrix(matTransform);

	GAME_ENGINE->DrawBitmap(m_BmpHeroPtr, Rect());

	GAME_ENGINE->SetColor(COLOR(255, 255, 255));
	if (m_OnFloor) GAME_ENGINE->DrawString(String("on floor"), 10, 10);
	else GAME_ENGINE->DrawString(String("not on floor"), 10, 10);
}

void Hero::Idle()
{
	if (m_NewVel.x == 0)
	{
		m_ActionState = ActionState::IDLE;
		if (m_AccuTime > 1.0 / FOUR_FR_PER_SEC)
		{
			m_AccuTime = 0;
			m_CurrentFrame = ++m_CurrentFrame % FOUR_FR;
		}
	}
}

void Hero::Move()
{
	if (GAME_ENGINE->IsKeyboardKeyDown('Q'))
	{
		if (m_OnFloor)m_ActionState = ActionState::WALK;
		m_NewVel.x = -m_VelAmount;
		MoveAnim();
		m_HeroScale = DOUBLE2(-1,1);
	}
	if (GAME_ENGINE->IsKeyboardKeyDown('D'))
	{
		if (m_OnFloor)m_ActionState = ActionState::WALK;
		m_NewVel.x = m_VelAmount;
		MoveAnim();
		m_HeroScale = DOUBLE2(1, 1);
	}
	if (GAME_ENGINE->IsKeyboardKeyDown(VK_SHIFT) && GAME_ENGINE->IsKeyboardKeyDown('Q'))
	{
		if (m_OnFloor)m_ActionState = ActionState::RUN;
		MoveAnim();
		m_NewVel.x = -m_VelAmount*2.5;
		m_HeroScale = DOUBLE2(-1, 1);
	}
	if (GAME_ENGINE->IsKeyboardKeyDown(VK_SHIFT) && GAME_ENGINE->IsKeyboardKeyDown('D'))
	{
		if (m_OnFloor)m_ActionState = ActionState::RUN;
		MoveAnim();
		m_NewVel.x = m_VelAmount*2.5;
		m_HeroScale = DOUBLE2(1, 1);
	}
}

void Hero::MoveAnim()
{
	if (m_AccuTime > 1.0 / SIX_FR_PER_SEC)
	{
		m_AccuTime = 0;
		m_CurrentFrame = ++m_CurrentFrame % SIX_FR;
	}
}

void Hero::Jump()
{
	if (m_OnFloor)
	{
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_SPACE))
		{
			m_NewVel.y = -m_VelAmount * 3;
		}
	}
	if (!m_OnFloor)
	{
		m_ActionState = ActionState::JUMP;
		/*if (m_AccuTime > 1.0 / THREE_FR_PER_SEC)
		{
			m_AccuTime = 0;
			m_CurrentFrame = ++m_CurrentFrame % THREE_FR;
		}*/
		m_CurrentFrame = 2;
	}
}


RECT Hero::Rect()
{
	RECT r;

	if (m_ActionState == ActionState::IDLE) r.top = CLIP_HEIGHT * 0;
	else if (m_ActionState == ActionState::WALK) r.top = CLIP_HEIGHT * 1;
	else if (m_ActionState == ActionState::RUN) r.top = CLIP_HEIGHT * 2;
	else if (m_ActionState == ActionState::JUMP) r.top = CLIP_HEIGHT * 3;
	else if (m_ActionState == ActionState::ATTACK) r.top = CLIP_HEIGHT * 4;

	r.bottom = CLIP_HEIGHT + r.top;
	r.left = CLIP_WIDTH * m_CurrentFrame;
	r.right = CLIP_WIDTH + r.left;

	return r;
}

void Hero::ApplyImpulse()
{
	m_J = m_Mass * (m_NewVel - m_Vel) / PhysicsActor::SCALE;
	m_ActHeroPtr->ApplyLinearImpulse(m_J);
}

DOUBLE2 Hero::GetPosition()
{
	return m_ActHeroPtr->GetPosition();
}

// ======== Collision ========
void Hero::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	m_OnFloor = true;
}

void Hero::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	m_OnFloor = false;
}

void Hero::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}

