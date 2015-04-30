#pragma once
#include "Entity.h"

class EnemyBase : public Entity
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	// Methods
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);

	virtual void Tick(double deltaTime);
	virtual void Paint();
	virtual void RemoveEnemy();
	virtual int GetHealth() { return m_Health; }
	virtual int GetDirection();
	virtual void SetHealth(int health);
	virtual DOUBLE2 GetPosition() { return m_ActPtr->GetPosition(); }

protected:
	// Methods
	virtual void MoveTowardHero(double deltaTime);
	virtual void Attack(double deltaTime);
	virtual void DealDamage();
	// Inheritance Methods
	virtual void Init();
	virtual void UpdateVariables(double deltaTime);
	virtual void Anim();
	virtual RECT Rect();
	virtual void CreateWorldMatrix();

	// Class dependable constants
	const int BASE_DAMAGE = 3;
	const int CLIP_SIZE = 48;
	const int WALK_FR = 2;
	const int WALK_FR_PER_SEC = 6;
	const int MOVE_RANGE = 600;
	const int ATT_FR = 3;
	const int ATT_FR_PER_SEC = 2;

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
	Bitmap* m_BmpNpc1Ptr = nullptr;
};

