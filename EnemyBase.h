#pragma once
#include "Entity.h"

#include "MyGame.h"
#include "PickUpList.h"
#include "EnemyList.h"
#include "MainGame.h"
#include "PickUpBase.h"
#include "Doritos.h"
#include "HealthUp.h"
#include "Hero.h"

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
	virtual void Attack(double deltaTime) = 0;
	virtual void DealDamage();
	// Inheritance Methods
	virtual void Init();
	virtual void UpdateVariables(double deltaTime);
	virtual void Anim() = 0;
	virtual RECT Rect() = 0;
	virtual void CreateWorldMatrix();
	virtual void MoveTowardHero(double deltaTime) = 0;

	// Class dependable constants
	//GraveKeepr
	const int BASE_DAMAGE_GRAVEKEEPER = 3;
	const int WALK_FR_GRAVEKEEPER = 2;
	const int WALK_FR_PER_SEC_GRAVEKEEPER = 6;
	const int MOVE_RANGE_GRAVEKEEPER = 600;
	const int ATT_FR_GRAVEKEEPER = 3;
	const int ATT_FR_PER_SEC_GRAVEKEEPER = 2;
	//NightSpirit
	const int BASE_DAMAGE_NIGHTSPIRIT = 3;
	const int IDLE_FR_NIGHTSPIRIT = 3;
	const int WALK_FR_NIGHTSPIRIT = 3;
	const int WALK_FR_PER_SEC_NIGHTSPIRIT = 6;
	const int MOVE_RANGE_NIGHTSPIRIT = 600;
	const int ATT_FR_NIGHTSPIRIT = 3;
	const int ATT_FR_PER_SEC_NIGHTSPIRIT = 2;


	int m_ClipSize = 0;

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
	Bitmap* m_BmpPtr = nullptr;
};

