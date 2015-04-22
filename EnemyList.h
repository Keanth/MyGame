#pragma once
class Enemy;
class BulletList;
class Doritos;
class PickUpList;
class Hero;
class EnemyList
{
public:
	EnemyList(PhysicsActor* hero);
	virtual ~EnemyList();

	EnemyList(const EnemyList&) = delete;
	EnemyList& operator=(const EnemyList&) = delete;

	bool Add(Enemy* enemyPtr);
	bool Remove(Enemy* enemyPtr);
	void RemoveAll();
	void Tick(double deltaTime);
	void Paint();
	bool IsHit(PhysicsActor* actOtherPtr);
	int GetSize();
	bool HeDead();

private:
	const static int NR_OF_ENEMIES = 1;
	std::vector<Enemy*> m_EnemyPtrArr;
	void AddDoritos();

	Doritos* m_DoritosPtr = nullptr;
	PickUpList* m_PickUpListPtr = nullptr;
	PhysicsActor* m_ActHeroPtr = nullptr;
	bool m_Dead = false;
};

