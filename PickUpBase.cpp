#include "stdafx.h"
#include "PickUpBase.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

PickUpBase::PickUpBase()
{
	m_BmpPickUpPtr = new Bitmap(String("./Assets/Images/Sym.png"));
}

PickUpBase::~PickUpBase()
{
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

	r.top = CLIP_POS.y * CLIP_SIZE;
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
		m_CurrentFrame = (++m_CurrentFrame % FR) + CLIP_POS.x;
	}
}
