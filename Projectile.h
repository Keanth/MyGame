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
	virtual void Tick(double deltaTime);
	virtual void Paint();
	virtual DOUBLE2 GetPosition() { return m_ActBulletPtr->GetPosition(); }
	virtual PhysicsActor* GetActor() { return m_ActBulletPtr; }
	virtual bool Remove();
	virtual void SetPause();

protected:
	void CreateMatrix();
	virtual RECT Rect() = 0;
	DOUBLE2 m_HeroPos;
	PhysicsActor* m_ActBulletPtr = nullptr;

	void Init();

	enum class LEVEL
	{
		LEVEL1,
		LEVEL2,
		LEVEL3
	};

	static const int BASE_DAMAGE = 1;
	static const int INITIAL_EXP = 0;
	static const int BULLET_SPEED = 1000;
	static const int BULLET_OFFSET = 5;
	static const int BULLET_HIT_REGION = 5;
	static const double DEFAULT_BULLET_DESPAWN_TIME;
	int m_Direction = 0;

	//PolarStar
	static const int BULLET_WIDTH_POLARSTAR = 32;
	static const int BULLET_HEIGHT_POLARSTAR = 4;
	//NightSpirit
	static const int BULLET_WIDTH_NIGHTSPIRIT = 64;
	static const int BULLET_HEIGHT_NIGHTSPIRIT = 32;

	int m_BulletWidth = 0;
	int m_BulletHeight = 0;

	// Bitmap Bank
	Bitmap* m_BmpArrowPtr = nullptr;

	double m_BulletTimer = 0.0;
	double m_BulletDespawnTime = DEFAULT_BULLET_DESPAWN_TIME;

};

