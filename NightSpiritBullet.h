#pragma once
#include "Projectile.h"

class BitmapManager;
class NightSpiritBullet : public Projectile
{
public:
	NightSpiritBullet(DOUBLE2 pos, int direction);
	virtual ~NightSpiritBullet();

	NightSpiritBullet(const NightSpiritBullet&) = delete;
	NightSpiritBullet& operator= (const NightSpiritBullet&) = delete;

	virtual void Tick(double deltaTime);
	virtual void Paint();

	static int m_InstanceCounter;

private:
	RECT Rect();
};

