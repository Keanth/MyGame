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

private:

	const int CLIP_SIZE = 32;
	DOUBLE2 CLIP_POS = DOUBLE2(2, 4);

	int FR = 2;
	int FR_PER_SEC = 4;
};

