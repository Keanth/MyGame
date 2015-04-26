#pragma once
#include "PickUpBase.h"

class Doritos : public PickUpBase
{
public:
	Doritos(DOUBLE2 position, Hero* hero);
	virtual ~Doritos();

	Doritos(const Doritos&) = delete;
	Doritos& operator=(const Doritos&) = delete;

	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	void Tick(double deltaTime);
	void Paint();

private:
	const int BASE_AMOUNT = 1;
};

