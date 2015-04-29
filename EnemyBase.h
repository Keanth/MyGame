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
	void RemoveEnemy();
	int GetHealth();
	int GetDirection();
	void SetHealth(int health);
	DOUBLE2 GetPosition() { return m_ActPtr->GetPosition(); }

private:


};

