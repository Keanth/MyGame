#pragma once
#include "MyGame.h"
#include "ContactListener.h"

class EnemyList;
class PolarStarBullet;
class BulletList : public ContactListener
{
public:
	BulletList(EnemyList* enemyListPtr);
	virtual ~BulletList();

	BulletList(const BulletList&) = delete;
	BulletList& operator=(const BulletList&) = delete;

	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);

	void Tick(double deltaTime, int direction);
	void Paint();
	void Remove(PolarStarBullet* ArrowPtr);
	void ShootHandler();
	void SetActor(PhysicsActor* actOtherPtr);
	bool IsHit();


private:
	double m_BulletTimer = 0.0;
	const static int NR_OF_MAX_BULLETS = 10;
	std::vector<PolarStarBullet*> m_BulletPtrArr;
	bool m_IsShootWorthy = true;

	DOUBLE2 m_HeroPos;
	int m_HeroDirection;

	bool m_IsHit = false;
	
	EnemyList* m_EnemyListPtr = nullptr;
};

