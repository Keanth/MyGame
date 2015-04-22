#pragma once
#include "PickUpBase.h"

class Doritos : public PickUpBase
{
public:
	Doritos(DOUBLE2 position, PhysicsActor* hero);
	virtual ~Doritos();

	Doritos(const Doritos&) = delete;
	Doritos& operator=(const Doritos&) = delete;

	void Tick(double deltaTime);
	void Paint();
};

