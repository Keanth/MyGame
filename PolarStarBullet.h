#pragma once
#include "Projectile.h"

class BitmapManager;
class PolarStarBullet : public Projectile 
{
public:
	PolarStarBullet(DOUBLE2 pos, int direction);
	virtual ~PolarStarBullet();

	PolarStarBullet(const PolarStarBullet&) = delete;
	PolarStarBullet& operator= (const PolarStarBullet&) = delete;

	virtual void Tick(double deltaTime);
	virtual void Paint();

	static int m_InstanceCounter;
	static int m_Exp;

};

