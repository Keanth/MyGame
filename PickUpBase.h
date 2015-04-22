#pragma once
#include "ContactListener.h"

class Hero;
class PickUpBase : public ContactListener
{
public:
	PickUpBase();
	PickUpBase(DOUBLE2 position, PhysicsActor* hero);
	virtual ~PickUpBase();

	PickUpBase (const PickUpBase&) = delete;
	PickUpBase& operator=(const PickUpBase&) = delete;

	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);

	virtual void Tick(double deltaTime);
	virtual void Paint();

protected:
	virtual void CreateMatrix();
	virtual RECT Rect();
	virtual void Anim();

	const int CLIP_SIZE = 32;
	DOUBLE2 CLIP_POS = DOUBLE2(0.0,0.0);

	int FR = 0;
	int FR_PER_SEC = 0;

	double m_AccuTime = 0;
	int m_CurrentFrame = 0;

	DOUBLE2 m_ActorPosition;
	double m_ActorAngle = 0;

	Bitmap* m_BmpPickUpPtr = nullptr;
	PhysicsActor* m_ActPickUpPtr = nullptr;
	PhysicsActor* m_ActHeroPtr = nullptr;

};

