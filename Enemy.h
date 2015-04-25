#pragma once
#include "Entity.h"
#include "Hero.h"

class Enemy : public Entity
{
public:
	Enemy(LevelOutdoor* level, Hero* hero, DOUBLE2 position);
	virtual ~Enemy();

	Enemy(const Enemy&) = delete;
	Enemy& operator=(const Enemy&) = delete;
	
	// Methods
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	virtual void Tick(double deltaTime);
	virtual void Paint();
	void RemoveEnemy();
	int GetHealth();
	int GetDirection();
	void SetHealth(int health);

private:
	// Methods
	void MoveTowardHero(double deltaTime);
	void Attack(double deltaTime);
	void DealDamage();
	// Inheritance Methods
	virtual void Init();
	virtual void UpdateVariables(double deltaTime);
	virtual void Anim();
	virtual RECT Rect();
	virtual void CreateWorldMatrix();


	// Class dependable constants
	static const int BASE_DAMAGE = 3;
	static const int CLIP_SIZE = 48;
	static const int WALK_FR = 2;
	static const int WALK_FR_PER_SEC = 6;
	static const int MOVE_RANGE = 600;
	static const int ATT_FR = 3;
	static const int ATT_FR_PER_SEC = 2;

	LevelOutdoor* m_LevelPtr = nullptr;
	Hero* m_HeroPtr = nullptr;

	static const int FULL_HEALTH = 100;
	int m_Health = FULL_HEALTH;

	PhysicsActor* m_ActIsHitPtr = nullptr;
	bool m_IsHit = false;

	DOUBLE2 m_PosDif;
	bool m_MoveWorthy = true;
	bool m_AttackWorthy = false;
	double m_AttackTime = 0.0;
	double m_DamageTime = 0.0;
	bool m_BoolDealDamage = true;

	DOUBLE2 m_Position; //CHECK

	// Bitmap Bank
	BitmapManager* m_BitmapManager = nullptr;
	Bitmap* m_BmpNpc1Ptr = nullptr;
};

