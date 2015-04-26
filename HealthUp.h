#pragma once
#include "PickUpBase.h"

class HealthUp : public PickUpBase
{
public:
	HealthUp(DOUBLE2 position, Hero* hero);
	virtual ~HealthUp();

	HealthUp(const HealthUp&) = delete;
	HealthUp& operator=(const HealthUp&) = delete;

	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	void Tick(double deltaTime);
	void Paint();

private:
	const int BASE_AMOUNT = 2;
};

