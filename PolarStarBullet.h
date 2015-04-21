#pragma once
#include "ContactListener.h"
class BitmapManager;
class PolarStarBullet
{
public:
	PolarStarBullet(DOUBLE2 pos, int direction);
	virtual ~PolarStarBullet();

	PolarStarBullet(const PolarStarBullet&) = delete;
	PolarStarBullet& operator= (const PolarStarBullet&) = delete;

	void Tick();
	void Paint();
	DOUBLE2 GetPosition() { return m_ActBulletPtr->GetPosition(); }
	PhysicsActor* GetActor() { return m_ActBulletPtr; }

	static int m_InstanceCounter;

private:
	RECT Rect();
	DOUBLE2 m_HeroPos;
	PhysicsActor* m_ActBulletPtr = nullptr;

	static const int BASE_DAMAGE = 1;
	static const int BULLET_WIDTH = 32;
	static const int BULLET_HEIGHT = 4;
	static const int BULLET_SPEED = 1000;
	static const int BULLET_OFFSET = 5;

	int m_Direction;

	// Bitmap Bank
	BitmapManager* m_BitmapManager = nullptr;
	Bitmap* m_BmpArrowPtr = nullptr;
};

