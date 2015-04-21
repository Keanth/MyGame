#pragma once
class Enemy;
class BulletList;
class EnemyList
{
public:
	EnemyList();
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
	void HeDead();

private:
	const static int NR_OF_ENEMIES = 1;
	std::vector<Enemy*> m_EnemyPtrArr;
};

