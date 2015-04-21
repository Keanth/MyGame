#pragma once
#include "PickUpBase.h"

class HealthUp : public PickUpBase
{
public:
	HealthUp(DOUBLE2 position);
	virtual ~HealthUp();

	HealthUp(const HealthUp&) = delete;
	HealthUp& operator=(const HealthUp&) = delete;

	void Tick(double deltaTime);
	void Paint();
};

