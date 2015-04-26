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
	static int m_Exp;

private:
	RECT Rect();
	DOUBLE2 m_HeroPos;
	PhysicsActor* m_ActBulletPtr = nullptr;

	const int BASE_DAMAGE = 1;
	static const int INITIAL_EXP = 0;
	const int BULLET_WIDTH = 32;
	const int BULLET_HEIGHT = 4;
	const int BULLET_SPEED = 1000;
	const int BULLET_OFFSET = 5;
	int BULLET_HIT_REGION = 5;
	int m_Direction;

	// Bitmap Bank
	Bitmap* m_BmpArrowPtr = nullptr;
};

