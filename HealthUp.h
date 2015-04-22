#pragma once
#include "PickUpBase.h"

class Hero;
class HealthUp : public PickUpBase
{
public:
	HealthUp(DOUBLE2 position, PhysicsActor* hero);
	virtual ~HealthUp();

	HealthUp(const HealthUp&) = delete;
	HealthUp& operator=(const HealthUp&) = delete;

	void Tick(double deltaTime);
	void Paint();
};

