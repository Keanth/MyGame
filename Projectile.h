#pragma once
#include "MyGame.h"

class Projectile
{
public:
	Projectile();
	virtual ~Projectile();

	Projectile(const Projectile&) = delete;
	Projectile& operator=(const Projectile&) = delete;

	//methods
	/*virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);*/
	virtual void Tick(double deltaTime);
	virtual void Paint();
	virtual DOUBLE2 GetPosition() { return m_ActBulletPtr->GetPosition(); }
	virtual PhysicsActor* GetActor() { return m_ActBulletPtr; }

protected:
	void CreateMatrix();
	RECT Rect();
	DOUBLE2 m_HeroPos;
	PhysicsActor* m_ActBulletPtr = nullptr;

	void Init();

	enum class LEVEL
	{
		LEVEL1,
		LEVEL2,
		LEVEL3
	};

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

