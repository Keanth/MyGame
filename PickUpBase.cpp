#include "stdafx.h"
#include "PickUpBase.h"
#include "DamageHero.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

PickUpBase::PickUpBase()
{
	m_BmpPickUpPtr = new Bitmap(String("./Assets/Images/Sym.png"));
}

PickUpBase::~PickUpBase()
{
	delete m_ActPickUpPtr;
	delete m_BmpPickUpPtr;
}

void PickUpBase::Tick(double deltaTime)
{
	m_AccuTime += deltaTime;
	Anim();
}

void PickUpBase::Paint()
{
	CreateMatrix();
	GAME_ENGINE->DrawBitmap(m_BmpPickUpPtr, Rect());
}

void PickUpBase::CreateMatrix()
{
	MATRIX3X2 matPivot, matTransform, matTranslate;
	matPivot.SetAsTranslate(DOUBLE2(-CLIP_SIZE / 2, -CLIP_SIZE / 2));
	matTranslate.SetAsTranslate(m_ActorPosition);
	matTransform = matPivot*matTranslate;
	GAME_ENGINE->SetWorldMatrix(matTransform);
}

RECT PickUpBase::Rect()
{
	RECT r;

	r.top = int(CLIP_POS.y * CLIP_SIZE);
	r.bottom = r.top + CLIP_SIZE;
	r.left = m_CurrentFrame * CLIP_SIZE;
	r.right = r.left + CLIP_SIZE;

	return r;
}

void PickUpBase::Anim()
{
	if (m_AccuTime > 1.0 / FR_PER_SEC)
	{
		m_AccuTime = 0;
		m_CurrentFrame = int((++m_CurrentFrame % FR) + CLIP_POS.x);
	}
}

void PickUpBase::BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
	if ((actOtherPtr == m_ActHeroPtr))
	{
		
	}
}

void PickUpBase::EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr)
{
}

void PickUpBase::ContactImpulse(PhysicsActor *actThisPtr, double impulse)
{

}